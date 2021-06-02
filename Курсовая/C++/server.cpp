#include <iostream>
#include <cpp_httplib/httplib.h>
using namespace std;
using namespace httplib;
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <vector>

#include <nlohmann/json.hpp>
#define SQLITE_API __declspec(dllimport)
#include <sqlite3/sqlite3.h> 
using namespace std;
using json = nlohmann::json;

sqlite3* db;



using Record = std::vector<std::string>;
using Records = std::vector<Record>;



int select_callback(void* p_data, int num_fields, char** p_fields, char** p_col_names)
{
	Records* records = static_cast<Records*>(p_data);
	try {
		records->emplace_back(p_fields, p_fields + num_fields);
	}
	catch (...) {
		// abort select on failure, don't let exception propogate thru sqlite3 call-stack
		return 1;
	}
	return 0;
}

vector<vector<string>>  sort_12(vector<vector<string>> arr, int size)
{
	vector<string> tmp;
	for (int i = 0; i < size - 1; ++i) // i - номер прохода
	{
		for (int j = 0; j < size - 1; ++j) // внутренний цикл прохода
		{
			if (stoi(arr[j + 1][1]) > stoi(arr[j][1]))
			{
				tmp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = tmp;
			}
		}
	}
	return arr;
}



void gen_response(const Request& req, Response& res) {
	//cout << "=================================================="<<endl;
	string score = req.get_param_value("SCORE");
	string name = req.get_param_value("name");
	int position=1;
	int record_score=-1;
	
	// Проверка на созданность бд
	sqlite3* DB;
	int exit = sqlite3_open("persons.db", &DB);

	char* errmsg = 0;
	string stmt = "SELECT * FROM PERSON";
	Records records;
	//cout << "start" << endl;
	int ret = sqlite3_exec(DB, stmt.c_str(), select_callback, &records, &errmsg);
	vector<vector<string>> list_player;
	//cout << "start_1" << endl;
			for (auto& record : records) { // ПОЛУЧЕНИЕ ПОЗИЦИИ
				//cout << record[0] <<" "<<record[2]<< endl;
				if (record[0]==name) // Если текущий игрок
				{
					record_score = stoi(record[1]);
				}
				string r1 = record[0];
				string r2 = record[1];
				vector<string> trm;
				trm.push_back(r1);
				trm.push_back(r2);
				list_player.push_back(trm);
			}
			//cout << "start_2" << endl;
			if (record_score == -1) //  Значит новый игрок
			{
				record_score = stoi(score);
			}
			if (stoi(score)>record_score)
			{
				record_score = stoi(score);
			}
			vector<vector<string>>new_players_list = sort_12(list_player, list_player.size());

			//cout << "$$$$$$$$$$"<< endl;
			int i = 1;
			position = list_player.size();

			//cout << "start2" << endl;
	for (auto& record : new_players_list) { // ПОЛУЧЕНИЕ ПОЗИЦИИ	
		//cout << record[1] << " = "<<score << " = "<< i << " | "<<(stoi(score) >= stoi(record[1])) <<endl;

		if (stoi(score) >= stoi(record[1]))
		{
			position = i;
			break;
		}
		i++;
	}

	//cout << "position" << position << endl;
	json j = { {"position",position},{"record_score",record_score} };

	sqlite3_close(DB);
			res.set_content(j.dump(), "text/json; charset=UTF-8");// Вывод позиции и рекорда


}


void gen_response_set(const Request& req, Response& res) {
	auto score = req.get_param_value("SCORE");
	string name = req.get_param_value("name");

	sqlite3* DB;
	int exit = sqlite3_open("persons.db", &DB);
	int last_record=0;

	char* errmsg = 0;
	string stmt = "SELECT * FROM PERSON";
	Records recordsD;
	int ret = sqlite3_exec(DB, stmt.c_str(), select_callback, &recordsD, &errmsg);

	bool is_available = false;
	for (auto& record : recordsD) { // ПОЛУЧЕНИЕ ПОЗИЦИИ
		cout << name << record[0] << endl;
		if (name == record[0])
		{
			last_record = stoi(record[1]);
			is_available = true;
		}
		}
	cout <<is_available << "is" << endl;

	if (is_available) // update
	{
		cout << score << last_record;
		if (stoi(score) > last_record)
		{
			cout << "update" << endl;



			std::stringstream UpdateQuery;
			UpdateQuery << "UPDATE PERSON "
					"SET RECORD = '" << score
				<< "' WHERE LOGIN = '" << name<< "'";
			//cout << UpdateQuery.str();

			sqlite3_stmt* UpdateStmt;
			sqlite3_prepare(DB, UpdateQuery.str().c_str(), UpdateQuery.str().size(), &UpdateStmt, NULL);

			cout << "Stepping Update Statement" << endl;
			if (sqlite3_step(UpdateStmt) != SQLITE_DONE) cout << "Didn't UpdateItem!" << endl;
		}
	}
	else { // insert
		cout << "insert" << endl;



		std::stringstream insertQuery;
		insertQuery << "INSERT INTO PERSON (LOGIN, RECORD)"
			" VALUES ('" << name
			<< "', " << score << ")";
		sqlite3_stmt* insertStmt;
		sqlite3_prepare(DB, insertQuery.str().c_str(), insertQuery.str().size(), &insertStmt, NULL);

		cout << "Stepping Insert Statement" << endl;
		if (sqlite3_step(insertStmt) != SQLITE_DONE) cout << "Didn't Insert Item!" << endl;
			
	}

	sqlite3_close(DB);
	res.set_content("1", "text/html");// Вывод статуса успешной операции


}

int main()
{
	setlocale(LC_ALL, "Russian");
	// Проверка на созданность бд
	sqlite3* DB;
	std::string sql = "CREATE TABLE PERSON("
		"LOGIN          TEXT    NOT NULL, "
		"RECORD         TEXT     NOT NULL );";
	int exit = 0;
	exit = sqlite3_open("persons.db", &DB);
	char* messaggeError;
	exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

	printf("Autocommit: %d\n", sqlite3_get_autocommit(DB));
	//if (exit != SQLITE_OK) {
	//	std::cerr << "Создание таблицы" << std::endl;
	//	sqlite3_free(messaggeError);
	//}
	//else {
	//	std::cout << "Таблица уже создана" << std::endl;
	//}
	sqlite3_close(DB);


	//string str = "SELECT * " + to_string(exit) + "WHERE";
	//cout << str;



	Server svr;
	svr.Post("/rating", gen_response);    // Виджет
	svr.Post("/set_rating", gen_response_set);    // Виджет
	std::cout << "Start server... OK\n";
	svr.listen("localhost", 3000);


	}

