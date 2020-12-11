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

![](https://cdn1.savepice.ru/uploads/2020/11/20/95ba3648b0a85ed599ea514b69e08db8-full.jpg)
<p align=center>Рисунок 1. Созданный key «API key». 

Далее мы будем использовать его для решения поставленных задач.
Я составил запрос на получение прогноза погоды для города  Симферополя с почасовым интервалом, в градусах Цельсия, на русском языке.

Запрос на погоду: http://api.openweathermap.org/data/2.5/onecall?lat=44.957191&lon=34.11079&exclude=minutely&lang=ru&units=metric&appid=601ce3f27452b85666c9cf828acab787

<p align="center">1</p>
<hr>
Данный запрос позволит мне использовать данные погоды, которые в формате json были предоставлены мне в ответ на запрос погоды(рис.2).

![](https://cdn1.savepice.ru/uploads/2020/11/20/79b7485182015e248cde31489634eecc-full.jpg)
<p align=center>Рисунок 2. Ответ на запрос погоды.
Также, для дальнейшей работы, мне понадобилось время местности, для которой  брались данные о погоде. Я сформировал запрос на время, который предоставляет время необходимой местности в формате json.

Запрос на время: http://worldtimeapi.org/api/timezone/Europe/Simferopol

![](https://cdn1.savepice.ru/uploads/2020/11/20/f06e133df25e66ba0a2361dad6019555-full.jpg)
<p align=center>Рисунок 3. Ответ на запрос время.

Я создал серверное приложение, которое создаёт сервер. Когда пользователь вводит http://localhost:3000/ , тогда он должен получить краткий прогноз погоды в виде виджета,  если же пользователь вводит http://localhost:3000/raw , ему выводиться json файл, который нужен будет для работы клиентского приложения Python.
Для этого нужно загрузить в папку с главным .срр файлом два файла для работы серверного приложения: json.h и httplib.h. Данные файлы я заранее скачал из репозитория https://github.com/yhirose/cpp-httplib . 
Также, в папку с главным .срр файлом нужно загрузить файл с шаблоном виджета, который я скачал по ссылке https://vladimirchabanov.github.io/Lab1_fils/widget_template.html . 
<p align="center">2</p>
<hr>
Код С++:

```

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
```
<p align="center">3</p>
<hr>
![](https://cdn1.savepice.ru/uploads/2020/11/20/486373b77e16dbbed256594a72c110b1-full.jpg)
<p align=center>Рисунок 4. Результат при вводе http://localhost:3000/.

А вот и результат при вводе http://localhost:3000/raw:

![](https://cdn1.savepice.ru/uploads/2020/11/20/e97ceb3e0d419281e76afe8d3945f61d-full.jpg)
Рисунок 5. Результат при вводе http://localhost:3000/raw.

Следующим шагом стало создание клиентского приложения, которое принимает значение файла формата json, который находится на http://localhost:3000/raw, и на основе этих данных создаёт виджет(рис.6).
 	К сожалению, я не успел в срок дописать код клиентской программы Python, но есть его часть:
<p align="center">4</p>
<hr>

Часть кода на Python:

```

def right_click(event):
r = requests.get('http://localhost:3000/raw')

from tkinter import *
import requests
import json


j = []

r = requests.get('http://localhost:3000/raw')


j = r.text
parsed_string["temp"] = json.loads(j)
parsed_string["description"].encode('l1').decode() = json.loads(j)

j1 = j["temp"]
j2 = j["description"]

root = Tk()

root.bind("<Buttone-3>",)
root.title("Погода")
root.geometry('140*200')

one = Label(root, text = “Симферополь", bg = "orange", width = 20)
two = Label(root, text = j1, bg = "yellow", width = 30, height=20)
three = Label(root, text = f2 + "°C", bg = "white", width = 10)
four = Label(root,bg = "orange", height = 3, width = 20)

root.mainloop()

```

![1](https://cdn1.savepice.ru/uploads/2020/11/20/5c2123f7235c2e3e7447e2ef27d009ba-full.png)
<p align=center>Рисунок 6. Вид эскиза виджета на Python.

Для защиты работы я скачал программу ngrok с сайта https://ngrok.com/ .  Данная программа позволило создать туннель к localhost. Открыв программу, мне осталось лишь ввести ngrok.exe http 3000. Мой сервер будет доступен из интернета(Рис.7).

![](https://cdn1.savepice.ru/uploads/2020/11/20/bdc9a9067d2c400b35d04a4bb6d14a73-full.jpg)
<p align=center>Рисунок 7. Созданный туннель.


Если прописать в браузере http://127.0.0.1:4040  можно увидеть статистику по запросам, проходящим через туннель.

<h3>Вывод:</h3>

Закрепил навыки разработки многофайловыx приложений. Изучил способы работы с API web-сервиса. Изучил процесс сериализации/десериализации данных в/из json. Получил базовое представление о сетевом взаимодействии приложений.
Хоть и не всё получилось сделать в данной лабораторной работе, но общее представление работы всех необходимых для выполнения данного задания были узнаны и запомнены.