#include <iostream>
#include <cpp_httplib/httplib.h>
#include <nlohmann/json.hpp>
#include <string>
#include <fstream>
#include <cmath>
#include <conio.h>
using json = nlohmann::json;
using namespace std;
using namespace httplib;

void gen_response(const Request& req, Response& res) 
{
	Client cli("http://worldtimeapi.org");
	auto p = cli.Get("/api/timezone/Europe/Simferopol");

	string time = p->body;

	json j = json::parse(time);

	Client cliw("api.openweathermap.org");
	auto f = cliw.Get("/data/2.5/onecall?lat=44.957191&lon=34.11079&exclude=minutely&lang=ru&units=metric&appid=601ce3f27452b85666c9cf828acab787");
	
	string weather = f->body;

	json h = json::parse(weather);
	
	cout << h["daily"][0]["weather"][0]["description"];

	ifstream file("weather.html"); 
	if (!(file.is_open())) 
	{
		cout << "File not find\n";
		cout << "exit";
	}
	else {

		string str;
		getline(file, str, '\0');

		string s1 = "{hourly[i].weather[0].description}";
		int num1 = size(s1);

		str.replace(str.find(s1), num1, h["daily"][0]["weather"][0]["description"]);

		string s2 = "{hourly[i].weather[0].icon}";
		string s3 = "{hourly[i].temp}";

		int k1 = size(s2);
		int k2 = size(s3);

		str.replace(str.find(s3), k2, to_string(int(round(double(h["daily"][0]["temp"]["day"])))));
		str.replace(str.find(s3), k2, to_string(int(round(double(h["daily"][0]["temp"]["day"])))));
		str.replace(str.find(s2), k1, h["daily"][0]["weather"][0]["icon"]);

		res.set_content(str, "text/html");
	}
}

void gen_response2(const Request& req, Response& res)
{
	Client cli("http://worldtimeapi.org");
	auto p = cli.Get("/api/timezone/Europe/Simferopol");

	string time = p->body;

	json h = json::parse(time);

	Client cliw("api.openweathermap.org");
	auto f = cliw.Get("/data/2.5/onecall?lat=44.957191&lon=34.11079&exclude=minutely&lang=ru&units=metric&appid=601ce3f27452b85666c9cf828acab787");

	string weather = f->body;

	json j = json::parse(weather);

	json s;
	int l;
	string v;
	s["temp"] = h["daily"][0]["temp"]["day"];
	s["description"] = h["daily"][0]["weather"][0]["description"];

	res.set_content( s , "text/json");
}

int main() {

	Server svr; 
	svr.Get("/", gen_response);
	svr.Get("/raw", gen_response2);
	std::cout << "Start server... OK\n";
	svr.listen("localhost", 3000); 
}

