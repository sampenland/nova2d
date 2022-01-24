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
		struct HighScore
		{
			int ID;
			std::string PlayerName;
			int PlayerScore;
		};

		class SQLManager
		{
			
		private:

			bool m_UsingSQL = false;

			std::string m_CurrentConnectionString = "";
			std::string m_CurrentDatabase = "";
			std::string m_CurrentTable = "";
			std::string m_User = "";
			std::string m_Password = "";

		public:

			SQLManager() { };

			/* 
				Creates a table with columns(automatically adds auto increment primary key : id)
				 - tableName = name for the table inside the database 
				 - columns   = map<string, string> like { 'age' : 'int(2)' , 'name' : 'varchar(20)' }		
			*/
			void CreateTableIfNotExist(std::string tableName, std::map<std::string, std::string> &columns)
			{
				std::string createQuery = "CREATE TABLE IF NOT EXISTS " + tableName + " ( id int NOT NULL AUTO_INCREMENT PRIMARY KEY, ";

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

			void Configure(std::string databaseName, std::string connectionString, std::string user, std::string pass)
			{
				m_UsingSQL = true;

				m_CurrentConnectionString = connectionString;
				m_User = user;
				m_Password = pass;

				std::string query = "CREATE DATABASE " + databaseName + ";";
				ExecuteNonResult(query,"-1","-1","-1","-1", true);
				m_CurrentDatabase = databaseName;

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

			/*
			Gets an array of high scores. Returns up to count results.
			MAKE SURE TO pass in a reference to a HighScore vector (&resultsOUT)
			*/
			void GetScores(int count, std::vector<HighScore>& resultsOUT)
			{
				CheckIfUsingSQL();

				try
				{
					sql::mysql::MySQL_Driver* driver;
					sql::Connection* conn;
					sql::ResultSet* resultSet;

					driver = sql::mysql::get_mysql_driver_instance();
					conn = driver->connect(m_CurrentConnectionString, m_User, m_Password);
					if (conn && conn->isValid())
					{
						sql::Statement* command = conn->createStatement();
						command->execute("USE " + m_CurrentDatabase);
						resultSet = command->executeQuery("SELECT id, name, score FROM scores ORDER BY score DESC LIMIT " + 
							std::to_string(count) + ";");

						std::vector<HighScore> results;

						while (resultSet->next())
						{
							HighScore h;
							h.ID = resultSet->getInt(1);
							h.PlayerName = resultSet->getString(2);
							h.PlayerScore = resultSet->getInt(3);

							results.push_back(h);
						}

						resultsOUT = results;

						if (command)
							delete command;

						if (conn)
							delete conn;
					}
				}
				catch (const sql::SQLException& e)
				{
					LOG(e.what());
					LOG("SQL error : could not get high scores");
					return;
				}
			}

			void RemoveScore(std::string playerName, int score)
			{
				ExecuteNonResult("DELETE FROM scores WHERE playerName = '" + playerName + "' AND score = '" + std::to_string(score) + "';");
			}

			/*
				Executes a query which does not return a result set (or is thrown away if returned)
			*/
			void ExecuteNonResult(std::string query, std::string connectionString = "-1",
				std::string table = "-1", std::string user = "-1", std::string pass = "-1", bool creatingDatabase = false)
			{

				CheckIfUsingSQL();

				m_CurrentConnectionString = connectionString == "-1" ? m_CurrentConnectionString : connectionString;
				m_CurrentTable = table == "-1" ? m_CurrentTable : table;
				m_User = table == "-1" ? m_User : user;
				m_Password = table == "-1" ? m_Password : pass;

				try
				{
					sql::mysql::MySQL_Driver* driver;
					sql::Connection* conn;

					driver = sql::mysql::get_mysql_driver_instance();
					conn = driver->connect(m_CurrentConnectionString, m_User, m_Password);
					if (conn && conn->isValid())
					{
						sql::Statement* command = conn->createStatement();
						if(!creatingDatabase) command->execute("USE " + m_CurrentDatabase);
						command->execute(query);

						if (command)
							delete command;
						
						if (conn)
							delete conn;
					}
				}
				catch (const sql::SQLException& e)
				{
					if (!creatingDatabase)
					{
						LOG(e.what());
						LOG("SQL error :" + query);
					}
				}
			};

			~SQLManager()
			{

			};

		};
	}
}