#include "Graph.hpp"
#include <sstream>
int main()
{
	Graph G;
	std::string line;

	std::cout << "Social Net Simulator CLI"<<std::endl;
	std::cout << "COMMANDS:" << std::endl;
	std::cout << "ADD USER <username>, ADD FRIEND <username1> <username2>, LIST FRIENDS <username>"<< std::endl;
	std::cout << "SUGGEST FRIENDS <username> <N>,  DEGREES OF SEPARATION <username1> <username2>" << std::endl;
	std::cout << "ADD POST <username> \"<post content>\", OUTPUT POSTS <username> <N>"<< std::endl;
	std::cout << "EXIT" << std::endl;

	while(true) {
		std::cout << "\n>";
		if(!getline(std::cin,line)) {
			break;
		}

		std::stringstream ss(line);
		std::string cmd;
		ss >> cmd;
		if (cmd=="ADD") {
			std::string sub;
			ss >> sub;
			if(sub=="USER") {
				std::string userName;
				ss>>userName;
				if(userName.empty()) {
					std::cout<<"Empty userName not allowed"<<std::endl;
				} else {
					std::string extra;
					std::getline(ss, extra);
					while (!extra.empty() && extra[0] == ' ')
						extra = extra.substr(1);
					if(!extra.empty()) {
						std::cout << "INCORRECT SYNTAX: ADD ONLY A SINGLE USER" << std::endl;
						std::cout << "COMMAND NOT EXECUTED" << std::endl;
					} else {
						G.addUser(userName);
					}
				}
			}
			else if(sub=="FRIEND") {
				std::string user1;
				std::string user2;
				ss>>user1>>user2;
				std::string extra;
				std::getline(ss, extra);
				while (!extra.empty() && extra[0] == ' ')
					extra = extra.substr(1);
				if(!extra.empty()) {
					std::cout << "INCORRECT SYNTAX: ADD A SINGLE FRIEND" << std::endl;
					std::cout << "COMMAND NOT EXECUTED" << std::endl;
				} else {
					G.addFriend(user1,user2);
				}
			}
			else if(sub=="POST") {
				std::string userName;
				ss >> userName;

				std::string content;
				std::getline(ss, content);

				while (!content.empty() && content[0] == ' ')
					content = content.substr(1);

				if (content.size() < 2 || content.front() != '"' || content.back() != '"') {
					std::cout << "INCORRECT SYNTAX: POST MUST BE ENCLOSED IN DOUBLE QUOTES"<<std::endl;
					std::cout << "COMMAND NOT EXECUTED" << std::endl;
					continue;
				}
				if(!content.empty()) {
					content = content.substr(1, content.size() - 2);
					G.addPost(userName, content);
				} else {
					G.addPost(userName,content);
				}
			}
			else {
				std::cout << "Unknown Command"<<std::endl;
			}
		}
		else if(cmd=="LIST") {
			std::string sub;
			ss>>sub;
			if(sub=="FRIENDS") {
				std::string userName;
				ss>>userName;
				std::string extra;
				std::getline(ss, extra);
				while (!extra.empty() && extra[0] == ' ')
					extra = extra.substr(1);
				if(!extra.empty()) {
					std::cout << "INCORRECT SYNTAX: COMMAND FOR A SINGLE USER" << std::endl;
				} else {
					G.listFriend(userName);
				}
			}
			else {
				std::cout << "Unknown Command\n";
			}
		}
		else if (cmd == "SUGGEST") {
			std::string sub;
			ss >> sub;

			if (sub == "FRIENDS") {
				std::string userName, nStr;
				ss >> userName >> nStr;

				bool isValid = !nStr.empty() && std::all_of(nStr.begin(), nStr.end(), ::isdigit);

				if (!isValid) {
					std::cout << "Error: n must be a non-negative integer."<<std::endl;
				}
				else {
					int n = std::stoi(nStr);
					G.suggestFriends(userName, n);
				}
			}
			else {
				std::cout << "Unknown Command"<<std::endl;
			}
		}

		else if(cmd=="DEGREES") {
			std::string sub;
			ss>>sub;
			if (sub =="OF") {
				std::string sub2;
				ss>>sub2;
				if(sub2=="SEPARATION") {
					std::string user1;
					std::string user2;
					ss>>user1>>user2;
					std::string extra;
					std::getline(ss, extra);
					while (!extra.empty() && extra[0] == ' ')
						extra = extra.substr(1);
					if(!extra.empty()) {
						std::cout << "INCORRECT SYNTAX: COMMAND FOR 2 USERS ONLY" << std::endl;
					} else {
						G.degreeOfSeparation(user1,user2);
					}
				}
				else {
					std::cout << "Unknown Command\n";
				}
			}
			else {
				std::cout << "Unknown Command\n";
			}
		}
		else if (cmd == "OUTPUT") {
			std::string sub;
			ss >> sub;

			if (sub == "POSTS") {
				std::string userName, nStr;
				ss >> userName >> nStr;
				bool isValid = !nStr.empty() && std::all_of(nStr.begin(), nStr.end(), ::isdigit);

				if (isValid || nStr=="-1") {
					int n = std::stoi(nStr);
					std::string extra;
					std::getline(ss, extra);
					while (!extra.empty() && extra[0] == ' ')
						extra = extra.substr(1);
					if(!extra.empty()) {
						std::cout << "INCORRECT SYNTAX" << std::endl;
					} else {
						G.outputPosts(userName, n);
					}
				}
				else {
					std::cout << "Error: n must be a non-negative integer or -1"<<std::endl;
				}
			}else {
				std::cout << "Unknown Command"<<std::endl;
			}
		}


		else if (cmd == "EXIT") {
			break;
		}
		else {
			std::cout << "Unknown Command\n";
		}

	}
	return 0;
}