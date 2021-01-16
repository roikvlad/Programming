#include <iostream>
#include <cpp_httplib/httplib.h>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>
using json = nlohmann::json;
using namespace std;
using namespace httplib;

void gen_response(const Request& req, Response& res) 
{
	Client cli("http://worldtimeapi.org");
	auto r = cli.Get("/api/timezone/Europe/Simferopol");
	
	Client cliw("api.openweathermap.org");
	auto w = cliw.Get("/data/2.5/onecall?lat=44.957191&lon=34.11079&exclude=minutely&lang=ru&units=metric&appid=601ce3f27452b85666c9cf828acab787");
	if (r && w) 
	{
		//проверка статуса ответа
		if (r->status == 200 && w->status == 200) 
		{
			//если всё впорядке 
			string time = r->body;
			json j = json::parse(time);
			int unixtime = j["unixtime"]; 
			string wea = w->body;
			json t = json::parse(wea);
			json cache;
			//создание нового прогноза погоды(по условию)
			
			//извлекаем кеш
			ifstream src("cache.json");
			if (src)
			{
				src >> cache;
			}

			double temp;
			string description;
			string icon;
			//проверка
			if (empty(cache)) 
			{
				cache["hourly"][47]["dt"] = 0;
			}

			if (int(cache["hourly"][47]["dt"]) + 3600 >= unixtime) //если будет прогноз
			{

				for (int i = 0; i < 48; i++)
				{
					if (abs(unixtime - cache["hourly"][i]["dt"]) <= 3600) 
					{
						temp = cache["hourly"][i]["temp"];
						description = cache["hourly"][i]["weather"][0]["description"];
						icon = cache["hourly"][i]["weather"][0]["icon"];

						break;
					}

				}

			}

			else //если прогноза не будет
			{
				temp = t["hourly"][0]["temp"];
				description = t["hourly"][0]["weather"][0]["description"];
				icon = t["hourly"][0]["weather"][0]["icon"];
				ofstream srco("cache.json");
				srco << t;
			}
			
			ifstream file("weather.html"); 
			string str;         //текст вышеупомянутого файла     
			getline(file, str, '\0');
		
			//замена данных
			string k1 = "{hourly[i].weather[0].description}";
			string k2 = "{hourly[i].weather[0].icon}";
			string k3 = "{hourly[i].temp}";

			int n1 = size(k1);
			int n2 = size(k2);
			int n3 = size(k3);

			str.replace(str.find(k1), n1, description);
			str.replace(str.find(k3), n3, to_string(int(round(temp))));
			str.replace(str.find(k3), n3, to_string(int(round(temp))));
			str.replace(str.find(k2), n2, icon);
		
			res.set_content(str, "text/html");
		}
		else 
		{
			cout << "Status code: " << r->status << endl;
		}

	}
	else 
	{
		auto er = r.error();
		cout << "Error code: " << er << endl;
	}
}

void gen_responseraw(const Request& req, Response& res) 
{
	Client cli("http://worldtimeapi.org");
	auto r = cli.Get("/api/timezone/Europe/Simferopol");

	Client cliw("api.openweathermap.org");
	auto w = cliw.Get("/data/2.5/onecall?lat=44.957191&lon=34.11079&exclude=minutely&lang=ru&units=metric&appid=601ce3f27452b85666c9cf828acab787");
	if (r && w) 
	{
		//проверяем статус ответа
		if (r->status == 200 && w->status == 200) 
		{
			//если проблем нет
			string time = r->body;
			json j = json::parse(time);
			int unixtime = j["unixtime"]; 
			string wea = w->body;
			json t = json::parse(wea);
			json cache;
			//кеш для двух часов(по условию)
			
			//извлекаем кеш 
			ifstream src("cache.json"); //файловая переменная
			if (src)
			{
				src >> cache;
			}

			double temp = 0;
			string description;
			string icon;
			//читаем всё, пока не встретим символ 0
			if (empty(cache)) 
			{
				cache["hourly"][47]["dt"] = 0;
			}

			if (int(cache["hourly"][47]["dt"]) + 3600 >= unixtime) 
			{
				//если есть прогноз
				for (int i = 0; i < 48; i++)
				{
					
					if (abs(unixtime - cache["hourly"][i]["dt"]) <= 3600) 
					{
						temp = cache["hourly"][i]["temp"];
						description = cache["hourly"][i]["weather"][0]["description"];
						icon = cache["hourly"][i]["weather"][0]["icon"];

						break;
					}

				}

			}

			else //если прогноза нет
			{
				
				temp = t["hourly"][0]["temp"];
				description = t["hourly"][0]["weather"][0]["description"];
				icon = t["hourly"][0]["weather"][0]["icon"];
				
				//новый кеш
				ofstream srco("cache.json");
				srco << t;
			}

			json str;
			str["temp"] = to_string(int(round(temp)));
			str["description"] = description;
			
			res.set_content(str.dump(), "text/json");
		}

		else 
		{
			cout << "Status code: " << r->status << endl;
		}
	}

	else 
	{
		auto er = r.error();
		cout << "Error code: " << er << endl;
	}
}

int main()
{
	Server svr;
	svr.Get("/", gen_response);
	svr.Get("/raw", gen_responseraw);
	std::cout << "Start server... OK\n";
	svr.listen("localhost", 3000);
}