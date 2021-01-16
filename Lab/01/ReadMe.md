<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе № 1<br> по дисциплине "Программирование"</h3>
<br><br>
<p>студента 1 курса группы ИВТ-б-о-201(2)<br>
Роик Владислав Вадимович<br>
направления подготовки 09.03.01 "Информатика и вычислительная техника"</p>
<br><br>
<table>
<tr><td>Научный руководитель<br> старший преподаватель кафедры<br> компьютерной инженерии и моделирования</td>
<td>(оценка)</td>
<td>Чабанов В.В.</td>
</tr>
</table>
<br><br>
<p align="center">Симферополь, 2020</p>
<hr>


<h2 align="center">Постановка задачи</h2>


Разработать сервис предоставляющий данные о погоде в городе Симферополе на момент запроса.  В качестве источника данных о погоде используйте: http://openweathermap.org/. В состав сервиса входит: серверное приложение на языке С++ и клиентское приложение на языке Python.
Серверное приложение (далее Сервер) предназначенное для обслуживания клиентских приложений и минимизации количества запросов к сервису openweathermap.org. Сервер должен обеспечивать возможность получения данных в формате JSON и виде html виджета (для вставки виджета на страницу будет использоваться iframe).
Клиентское приложение должно иметь графический интерфейс отображающий сведения о погоде и возможность обновления данных по требованию пользователя.


<h2 align="center">Выполнение работы</h2>


Для получения API Key я зарегистрировался на сайте http://openweathermap.org/. После регистрации в разделе API Keys создал новый Key с названием «API key»(рис.1).
	API key: **601ce3f27452b85666c9cf828acab787**

![](C:\Users\USER\Desktop\Programming\Lab\01\картинки\ключ.jpg)
Рисунок 1. Созданный key «API key». 

Далее мы будем использовать его для решения поставленных задач.
Я составил запрос на получение прогноза погоды для города  Симферополя с почасовым интервалом, в градусах Цельсия, на русском языке.

Запрос на погоду: http://api.openweathermap.org/data/2.5/onecall?lat=44.957191&lon=34.11079&exclude=minutely&lang=ru&units=metric&appid=601ce3f27452b85666c9cf828acab787

<p align="center">1</p>
<hr>
Данный запрос позволит мне использовать данные погоды, которые в формате json были предоставлены мне в ответ на запрос погоды(рис.2).

![](C:\Users\USER\Desktop\Programming\Lab\01\картинки\погода.jpg)
Рисунок 2. Ответ на запрос погоды.

Также, для дальнейшей работы, мне понадобилось время местности, для которой  брались данные о погоде. Я сформировал запрос на время, который предоставляет время необходимой местности в формате json.

Запрос на время: http://worldtimeapi.org/api/timezone/Europe/Simferopol

![](C:\Users\USER\Desktop\Programming\Lab\01\картинки\время.jpg)
Рисунок 3. Ответ на запрос время.

Я создал серверное приложение, которое создаёт сервер. Когда пользователь вводит http://localhost:3000/ , тогда он должен получить краткий прогноз погоды в виде виджета,  если же пользователь вводит http://localhost:3000/raw , ему выводиться json файл, который нужен будет для работы клиентского приложения Python.
Для этого нужно загрузить в папку с главным .срр файлом два файла для работы серверного приложения: json.h и httplib.h. Данные файлы я заранее скачал из репозитория https://github.com/yhirose/cpp-httplib . 
Также, в папку с главным .срр файлом нужно загрузить файл с шаблоном виджета, который я скачал по ссылке https://vladimirchabanov.github.io/Lab1_fils/widget_template.html . 
<p align="center">2</p>
<hr>
Код С++:

```C++
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
```
<p align="center">3</p>
<hr>
![](C:\Users\USER\Desktop\Programming\Lab\01\картинки\виджет.jpg)
Рисунок 4. Результат при вводе http://localhost:3000/.

А вот и результат при вводе http://localhost:3000/raw:

![](C:\Users\USER\Desktop\Programming\Lab\01\картинки\Приложение.png)
Рисунок 5. Результат при вводе http://localhost:3000/raw.

Следующим шагом стало создание клиентского приложения, которое принимает значение файла формата json, который находится на http://localhost:3000/raw, и на основе этих данных создаёт виджет(рис.6).
 	
<p align="center">4</p>
<hr>

Код на Python:

```Python
from tkinter import *
import json
import requests

def reload_data(event=None):
	try:
		response = requests.get('http://localhost:3000/raw').content.decode("utf8")
		forecast_j = json.loads(response)

		desc.config(text=str(forecast_j["description"]))
		temp.config(text=str(int(forecast_j["temp"])) + "°C")
	except requests.exceptions.ConnectionError:
		pass

root = Tk()
root.title("Погода")
root.bind("<Button-1>", reload_data)
root.geometry('250x200')

yellow = "#ffb84d"
white = "#ffffff"
w = 100        
h = 30

top_frame =    Frame(root, bg=yellow, width=w, height=h)
middle_frame = Frame(root, bg=white,  width=w, height=h*3)
bottom_frame = Frame(root, bg=yellow, width=w, height=h)

top_frame.pack(side=TOP, fill=X)
middle_frame.pack(expand=True, fill=BOTH)
bottom_frame.pack(side=BOTTOM, fill=X)

city = Label(top_frame, font=("Times New Roman", 12), text="Симферополь", bg=yellow)
desc = Label(top_frame, font=("Times New Roman", 12), bg=yellow)
temp = Label(middle_frame, font=("Times New Roman", 48), bg=white)

city.pack(pady=0)
desc.pack(pady=0)
temp.pack(expand=True)

reload_data()
root.mainloop()
```

![](C:\Users\USER\Desktop\Programming\Lab\01\картинки\Приложение.png)
Рисунок 6. Вид эскиза виджета на Python.

Для защиты работы я скачал программу ngrok с сайта https://ngrok.com/ .  Данная программа позволило создать туннель к localhost. Открыв программу, мне осталось лишь ввести ngrok.exe http 3000. Мой сервер будет доступен из интернета(Рис.7).

![](C:\Users\USER\Desktop\Programming\Lab\01\картинки\ngrok.jpg)
Рисунок 7. Созданный туннель.


Если прописать в браузере http://127.0.0.1:4040  можно увидеть статистику по запросам, проходящим через туннель.

<h3>Вывод:</h3>

Закрепил навыки разработки многофайловыx приложений. Изучил способы работы с API web-сервиса. Изучил процесс сериализации/десериализации данных в/из json. Получил базовое представление о сетевом взаимодействии приложений.
