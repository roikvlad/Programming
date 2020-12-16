<p align="center">МИНИСТЕРСТВО НАУКИ  И ВЫСШЕГО ОБРАЗОВАНИЯ РОССИЙСКОЙ ФЕДЕРАЦИИ<br>
Федеральное государственное автономное образовательное учреждение высшего образования<br>
"КРЫМСКИЙ ФЕДЕРАЛЬНЫЙ УНИВЕРСИТЕТ им. В. И. ВЕРНАДСКОГО"<br>
ФИЗИКО-ТЕХНИЧЕСКИЙ ИНСТИТУТ<br>
Кафедра компьютерной инженерии и моделирования</p>
<br>
<h3 align="center">Отчёт по лабораторной работе № 2<br> по дисциплине "Программирование"</h3>
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


Разработайте и зарегистрируйте навык для Алисы на сервисе ЯндексюДиалоги;

В качестве backend-a для навыка реализуйте приложение на языке С++ выполняющее следующие функции:

Составление продуктовой корзины:

Добавление продукта в корзину;
Удаление продукта из корзины;
Очистка корзины;
Вывод списка товаров в корзине;
Подсчёт стоимости товаров в корзине.
Вывод справочной информации по навыку;

Регистрацию webhook-ов сторонних сервисов;

Отправку данных на сторонние сервисы. 

В качестве стороннего сервиса реализуйте приложение на языке Python выполняющее следующие функции:

Ожидание данных о покупке;
Сохранение поступивших данных в excel-документ.


<h2 align="center">Выполнение работы</h2>

Во-первых, я подготовил серверную часть. В папке include проекта создал папку cpp_httplib и скопируйте туда файл httplib.h из скаченного ранее репозитория по ссылке https://github.com/yhirose/cpp-httplib. В папке include создал папку nlohmann и скопировал туда файл json.hpp, который уже был скачан на мой компьютер. Далее я написал код в C++ для нашего задания.

Код С++:

```

#include <iostream>
#include <string>
#include "cpp_httplib/httplib.h"
#include <vector>
#include "nlohmann/json.hpp"
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;
using namespace httplib;
using json = nlohmann::json;

// В этой функции формируем ответ сервера на запрос
void gen_response(const Request& req, Response& res) {
    // Выводим на экран тело запроса
    std::cout << req.body.c_str();
    // Здесь будет ответ, пока-что взят пример из документации
    std::string str = u8R"(
    {
      "response": {
        "text": "Здравствуйте! Это мы, хороводоведы.",
        "tts": "Здравствуйте! Это мы, хоров+одо в+еды.",
        "buttons": [
            {
                "title": "Надпись на кнопке",
                "payload": {},
                "url": "https://example.com/",
                "hide": true
            }
        ],
        "end_session": false
      },
      "version": "1.0"
    })";
    // Отправляем ответ
    res.set_content(str, "text/json; charset=UTF-8");
}


// В этой функции формируем ответ сервера на запрос
void gen_responseHook(const Request& req, Response& res) {
    ifstream lsrc("config.json");
    json config;
    lsrc >> config;

    //cout << config["webhooks"];

    if (req.method == "POST") {

        if (req.has_param("del"))
        {
            auto val_del = req.get_param_value("del");

            for (int i = 0; i < config["webhooks"].size(); i++)
            {
                cout << json(val_del) << endl;
                cout << " i = " << i << " " << config["webhooks"][i] << endl;
                if (config["webhooks"][i] == val_del)
                {
                    config["webhooks"].erase(i);
                    ofstream csrc("config.json");
                    csrc << config;
                }
            }

            //config["webhooks"].push_back(val_set);
        }
        //       
        if (req.has_param("set"))
        {
            auto val_set = req.get_param_value("set");
            /*cout << val_set;*/

            config["webhooks"].push_back(val_set);
            ofstream csrc("config.json");
            csrc << config;
        }


    }

    cout << config << endl;
    //cout << config["webhooks"].size();

    ifstream file("Webhooks.html"); // Файловая переменная
    string str;                 // Буфер. Тут будет текст файла
    getline(file, str, '\0');// str html страница изменить значения temp*2

    string word1 = "{webhooks_list}";
    int num1 = size(word1);

    string stro;
    for (int i = 0; i < config["webhooks"].size(); i++)
    {
        stro.append(u8"<div class=\"form - row align - items - center\"><div class = \"col\" ><input type = \"text\" value = \" ").append(config["webhooks"][i]).append(u8" \" class = \"form-control mb-2\" disabled></div><div class = \"col\"><button type = \"submit\" name = \"del\" value = \"").append(config["webhooks"][i]).append(u8"\" class = \"btn btn-danger mb-2\">Удалить</button></div></div>");

        //string() + string(config["webhooks"][i]) + string(" \" class = \"form-control mb-2\" disabled></div><div class = \"col\"><button type = \"submit\" name = \"del\" value = \"{Webhook URL}\" class = \"btn btn-danger mb-2\">Удалить</button></div></div>");

        for (int i = 0; i < stro.length(); i++)
        {
            if (stro[i] == '\\')
            {
                stro.erase(i);
            }
        }
    }

    //cout << "htnl" << stro;
    str.replace(str.find(word1), num1, stro);


    // Отправляем ответ
    res.set_content(str, "text/html; charset=UTF-8");// Вывод

}


//void delbckspl(string strnewconfig) {
//
//    for (int i = 0; i < strnewconfig.length(); i++)
//    {
//        if (strnewconfig[i] == '\\')
//        {
//            strnewconfig.erase(i);
//        }
//    }
//}

int main() 
{
    Server svr;                                         // Создаём сервер (пока-что не запущен)
    svr.Post("/", gen_response);                       // Вызвать функцию gen_response на post запрос
    svr.Post("/webhooks", gen_responseHook);           // Вызвать функцию gen_response на post запрос
    svr.Get("/webhooks", gen_responseHook);           // Вызвать функцию gen_response на post запрос
    std::cout << "Start server... OK\n";               // cout использовать нельзя


    //newconfig.parse("{\"webhooks\": []}");
    //cout << strnewconfig;
    ifstream src("config.json");
    if (!src)
    {
        //    json newconfig;
        string strnewconfig = "{\"webhooks\": []}";

        /* delbckspl(strnewconfig);*/
         // {"webhooks":["vk.com","yandex.ru","jsoneditoronline.org"]}

        json newconfig = json::parse(strnewconfig);


        ofstream csrc("config.json");
        csrc << newconfig;

    }
    ifstream lsrc("config.json");
    json config;
    lsrc >> config;

    cout << "first" << config << endl;



    svr.listen("localhost", 1234);         // Запускаем сервер на localhost и порту 1234
}
```


![](https://cdn1.savepice.ru/uploads/2020/12/16/7980b0b82df1e69286f4ca1ca2ebcb45-full.jpg)
<p align=center>Рисунок 1. Работающая серверная часть задания. 

<p align="center">1</p>
<hr>

Далее я подготовил Webhook URL для Алисы. Для этого я сделал следующие действия:
1.Запустил ранее скачанный ngrok указав http и порт, который слушает серверное приложение;
2.Скопировал URL расположенный в поле Forwarding(рис.2);
3.Свернул ngrok и не закрывал, пока выполнил лабораторную, иначе, при следующем запуске ngrok URL поменялся бы. 

Полученный URL:  https://b53ecb481a7f.ngrok.io 


![](https://cdn1.savepice.ru/uploads/2020/12/16/6d55f6ed45e587a2114c9946f23968d4-full.jpg)
<p align=center>Рисунок 2. Созданный URL в ngrok.

Далее нужно подготовить к работе  сервис Яндекс.Диалоги. В данном сервисе с создал аккаунт, который нужен для создания нового навыка. Навык я оформил по следующей инструкции:

1. Имя навыка. Имена всех навыков находятся в одном пространстве имён, то есть вам нужно выбрать уникальное имя не совпадающее с уже существующими. Проверка происходит после сохранения настроек. Т.к. мы делаем не публичный навык, обычно, рекомендуют добавлять к названию фамилию. Например: Погода Пупкин.
2. Активационное имя. Можно пропустить.
3. Backend. Выберите Webhook URL и в поле ниже вставьте URL полученный от ngrok.
4. Примечание: каждый раз, когда вы будете закрывать ngrok, при новом запуске ссылка будет изменяться и её также придётся менять в данном поле и перепубликовывать навык. Для этого нажмите кнопку Остановить диалог в разделе Общие сведения, затем замените URL в разделе Настройки и заново опубликуйте навык.
5. Голос. Выберите на своё усмотрение.
6. Хранилище. Установите галочку в поле Использовать хранилище данных в навыке;
7. Тип доступа. Приватный. В данном случае ваш навык будет доступен только под вашей учётной записью, другие пользователи не смогут его запустить.
8. Доступные поверхности. Не меняем.
9. Поля: Примеры запросов, Имя разработчика, Категорируя и Описание. Заполните на своё усмотрение.
10. Иконка. Используйте любую иконку.
11. Нажмите Сохранить, а затем Опубликовать.  

Проверил связь навыка с серверным приложением. Для этого написал рандомный текст в чате Алисы(рис.3).

![](https://cdn1.savepice.ru/uploads/2020/12/16/9693779dac75d759893ed0982bca3025-full.jpg)
<p align=center>Рисунок 3. Работа созданного навыка.

<p align="center">2</p>
<hr>

Далее я начал работу с клиенским приложением и к сожалению не смог дописать его до конца.

Часть кода на Python:

```

from flask import Flask, request
 
app = Flask(__name__)
 
@app.route('/', methods=['POST', 'GET'])
def index():
    if request.method == 'POST':
        return "Это POST запрос"
    if request.method == 'GET':
        return "Это GET запрос"
 
if __name__ == "__main__":
    app.run()

```

<h3>Вывод:</h3>

Закрепил навыки разработки многофайловыx приложений.  Изучил процесс сериализации/десериализации данных в/из json. Получил базовое представление о сетевом взаимодействии приложений.
Были получены знания и появился опыт работы с Навыками в Хоть и не всё получилось сделать в данной лабораторной работе, но общее представление работы всех необходимых для выполнения данного задания были узнаны и запомнены.

<p align="center">3</p>
<hr>

