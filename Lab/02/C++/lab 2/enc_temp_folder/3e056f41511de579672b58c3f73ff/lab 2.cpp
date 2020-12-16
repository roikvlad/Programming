﻿#include <iostream>
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
    Server svr;                            // Создаём сервер (пока-что не запущен)
    svr.Post("/", gen_response);           // Вызвать функцию gen_response на post запрос
    svr.Post("/webhooks", gen_responseHook);           // Вызвать функцию gen_response на post запрос
    svr.Get("/webhooks", gen_responseHook);           // Вызвать функцию gen_response на post запрос
    std::cout << "Start server... OK\n"; // cout использовать нельзя


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