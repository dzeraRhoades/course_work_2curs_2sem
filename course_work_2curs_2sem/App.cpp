#include "App.h"
#include<clocale>

App::App()
{
	setlocale(LC_ALL, "Russian");
	stations = Stations::Instance()->getStations();
	gen = new DeliveryGenerator();
}

App::~App()
{
	if (logCompany != nullptr)
		delete logCompany;
	if (container != nullptr)
		delete container;
	if (cmp != nullptr)
		delete cmp;
	delete gen;
}

void App::startApplication()
{
	menu();
}

void App::createDeliveries()
{
	Delivery del;
	for (int i = 0; i < 10000; i++)
	{
		if (i % 10000 == 0)
			std::cout << std::endl;
		del = gen->generateDelivery();
		try
		{
			logCompany->insert(&del);
		}
		catch (const std::exception&)
		{
			
		}
	}
	
}

//void App::setStations(std::vector<Station>& stations)
//{
//	std::ifstream f("towns.json", std::ifstream::binary);
//	if (!f.is_open())
//		throw std::exception("towns file can't be opened");
//
//	nlohmann::json js;
//	nlohmann::json town;
//	f >> js;
//
//	int towns_num = js.at("towns").size();
//
//	Station st;
//
//	for (int i = 0; i < towns_num; i++)
//	{
//		town = js.at("towns")[i];
//		for (int j = 0; j < town.at("neighbours").size(); j++) // adding neighbours
//		{
//			st.adjacentStations.push_back(town.at("neighbours")[j]);
//		}
//		st.index = i;
//		st.coords.x = town.at("x");
//		st.coords.y = town.at("y");
//		st.name = town.at("name");
//		stations.push_back(st);
//		st.adjacentStations.clear();
//	}
//
//	f.close();
//}

void App::menu()
{
	std::string buf = "";
	Delivery del;
	//std::vector<int> dels;
	while (true)
	{
		switch (menuTab)
		{
		case App::MENU::CHOOSE_CONTAINER:
			while (buf != "1" && buf != "2")
			{
				system("cls");
				std::cout << "Выберете контейнер:\n1) AVL\t2) std::vector\n>>";
				std::cin >> buf;
			}
			if (buf == "1")
			{
				cmp = new CmpForInt;
				container = new AvlContainer(cmp);
			}
			else
			{
				container = new VectorContainer;
			}
			logCompany = new Logistic(container);
			menuTab = MENU::CHOOSE_OPERATION;
			buf = "";
			break;
		case App::MENU::CHOOSE_OPERATION:
			while (buf.size() != 1 && (buf[0] < '1' || buf[0] > '6'))
			{
				system("cls");
				std::cout << "Выберете операцию:\n1) Вставка\t2) Поиск\t3) Удаление\n4) Найти доставки из\t5) Найти доставки в\n" <<
					"6) Найти доставки стоимостью выше\n7) Выход\n>>";
				std::cin >> buf;
			}
			menuTab = (MENU)(buf[0] - '0' + 1);
			buf = "";
			break;
		case App::MENU::INSERT:
			del = gen->generateDelivery(); // возмодно придется переделать на ручной ввод
			logCompany->insert(&del);
			del.getInfo();
			system("pause");
			menuTab = MENU::CHOOSE_OPERATION;
			break;
		case App::MENU::FIND:
			while (!atoi(buf.c_str()))
			{
				system("cls");
				std::cout << "Введите идентификатор доставки:\n>>";
				std::cin >> buf;
				if (buf.size() == 1 && buf[0] == '0')
					break;
			}
			try
			{
				logCompany->find(atoi(buf.c_str()));
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
			buf = "";
			system("pause");
			menuTab = MENU::CHOOSE_OPERATION;
			break;
		case App::MENU::ERASE:
			while (!atoi(buf.c_str()))
			{
				system("cls");
				std::cout << "Введите идентификатор доставки:\n>>";
				std::cin >> buf;
				if (buf.size() == 1 && buf[0] == '0')
					break;
			}
			try
			{
				logCompany->erase(atoi(buf.c_str()));
				std::cout << "успешно удалено" << std::endl;
			}
			catch (const std::exception& ex)
			{
				std::cout << ex.what() << std::endl;
			}
			system("pause");
			buf = "";
			menuTab = MENU::CHOOSE_OPERATION;
			break;
		case App::MENU::SEARCH_DELIVERY_FROM:
			system("cls");
			std::cout << "Введите город:\n>>";
			std::cin.ignore();
			std::getline(std::cin, buf);
			logCompany->findDeliveries(Logistic::SEARCH_TYPE::FROM, &buf);
			menuTab = MENU::CHOOSE_OPERATION;
			system("pause");
			break;
		case App::MENU::SEARCH_DELIVERY_TO:
			system("cls");
			std::cout << "Введите город:\n>>";
			std::cin.ignore();
			std::getline(std::cin, buf);
			logCompany->findDeliveries(Logistic::SEARCH_TYPE::TO, &buf);
			menuTab = MENU::CHOOSE_OPERATION;
			system("pause");
			break;
		case App::MENU::SEARCH_DELIVERY_COST:
			system("cls");
			while (true)
			{
				std::cout << "Введите пороговую стоимость:\n>>";
				std::cin >> buf;
				if (atoi(buf.c_str()) != 0 || (buf.size() == 1 && buf[0] == '0'))
				{
					int cost = atoi(buf.c_str());
					logCompany->findDeliveries(Logistic::SEARCH_TYPE::COST, &cost);
					break;
				}
			}
			menuTab = MENU::CHOOSE_OPERATION;
			buf = "";
			system("pause");
			break;
		case App::MENU::EXIT:
			return;
			break;
		default:
			break;
		}
	}
}
