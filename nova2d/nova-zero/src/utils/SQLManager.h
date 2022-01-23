#pragma once
#include <string>
#include <mysql/jdbc.h>
#include "../logging/logging.h"
#include <map>

namespace novazero
{
	using namespace logging;

	namespace utils
	{
		class SQLManager
		{
			
		private:

			bool m_UsingSQL = false;

			std::string m_CurrentConnectionString = "";
			std::string m_CurrentTable = "";
			std::string m_User = "";
			std::string m_Password = "";

			sql::Driver* m_Driver = nullptr;
			sql::Connection* m_Connection = nullptr;

		public:

			SQLManager()
			{
				try
				{
					m_Driver = get_driver_instance();
				}
				catch (const sql::SQLException& e)
				{
					m_Driver = nullptr;

					LOG(e.what());
					LOG("SQL error getting driver");
					return;
				}

			};

			/* 
				Creates a table with columns(automatically adds auto increment primary key : id)
				 - tableName = name for the table inside the database 
				 - columns   = map<string, string> like { 'age' : 'int(2)' , 'name' : 'varchar(20)' }		
			*/
			void CreateTableIfNotExist(std::string tableName, std::map<std::string, std::string> &columns)
			{
				std::string createQuery = "CREATE TABLE IF NOT EXISTS " + tableName + " ( id int NOT NULL AUTO_INCREMENT, ";

				std::map<std::string, std::string>::iterator it = columns.begin();
				for (; it != columns.end(); it++)
				{
					createQuery += it->first + " " + it->second + " ";
					if (std::next(it) != columns.end())
					{
						createQuery += ", ";
					}
					else
					{
						createQuery += " );";
						break;
					}
				}

				ExecuteNonResult(createQuery);
			}

			void Configure(std::string connectionString, std::string table, std::string user, std::string pass)
			{
				m_UsingSQL = true;

				m_CurrentConnectionString = connectionString;
				m_CurrentTable = table;
				m_User = user;
				m_Password = pass;
			}

			bool CheckIfUsingSQL()
			{
				if (!m_UsingSQL)
				{
					LOG("Cannot perform SQL query.");
					LOG("You must first enable SQL using n2dSQLConfigure();");
					return false;
				}

				return true;
			}

			void CreateScoreTable(int nameMaxSize, int scoreDigitCount)
			{
				std::map<std::string, std::string> columns;

				columns.insert(std::pair<std::string, std::string>("name", "varchar(" + std::to_string(nameMaxSize) + ")"));
				columns.insert(std::pair<std::string, std::string>("score", "int(" + std::to_string(scoreDigitCount) + ")"));

				CreateTableIfNotExist("scores", columns);
				m_CurrentTable = "scores";
			}

			void AddScore(std::string playerName, int score)
			{
				ExecuteNonResult("INSERT INTO scores(name, score) VALUES ('" + playerName + "', '" + std::to_string(score) + "');");
			}

			void RemoveScore(std::string playerName, int score)
			{
				ExecuteNonResult("DELETE FROM scores WHERE playerName = '" + playerName + "' AND score = '" + std::to_string(score) + "';");
			}

			/*
				Executes a query which does not return a result set (or is thrown away if returned)
			*/
			void ExecuteNonResult(std::string query, std::string connectionString = "-1",
				std::string table = "-1", std::string user = "-1", std::string pass = "-1")
			{

				CheckIfUsingSQL();

				m_CurrentConnectionString = connectionString == "-1" ? m_CurrentConnectionString : connectionString;
				m_CurrentTable = table == "-1" ? m_CurrentTable : table;
				m_User = table == "-1" ? m_User : user;
				m_Password = table == "-1" ? m_Password : pass;

				m_Connection = m_Driver->connect(m_CurrentConnectionString, m_User, m_Password);

				if (m_Connection && m_Connection->isValid())
				{
					sql::Statement* command = m_Connection->createStatement();
					command->execute(query);

					if (command)
						delete command;
				}

				if (m_Connection)
					delete m_Connection;


				m_Connection = nullptr;

			};

			~SQLManager()
			{

			};

		};
	}
}