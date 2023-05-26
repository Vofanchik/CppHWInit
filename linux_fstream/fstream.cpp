#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;

void replace_all( // для замены пробелов в тексте сообщения
	std::string& s,
	std::string const& toReplace,
	std::string const& replaceWith
) {
	std::string buf;
	std::size_t pos = 0;
	std::size_t prevPos;

	// Reserves rough estimate of final size of string.
	buf.reserve(s.size());

	while (true) {
		prevPos = pos;
		pos = s.find(toReplace, pos);
		if (pos == std::string::npos)
			break;
		buf.append(s, prevPos, pos - prevPos);
		buf += replaceWith;
		pos += toReplace.size();
	}

	buf.append(s, prevPos, s.size() - prevPos);
	s.swap(buf);
}

void setOwnerPermissions(string filename) { //удаление разрешений для всех, кроме владельца
	std::filesystem::permissions(
		filename,
		std::filesystem::perms::group_all | std::filesystem::perms::others_all,
		std::filesystem::perm_options::remove
	);
}

class User {
public:

	string _name;
	string _login;
	string _pass;


	User(string name, string login, string pass) :_name(name), _login(login), _pass(pass) {};
	User() {
		_name = "";
		_login = "";
		_pass = "";
	};

	friend fstream& operator >>(fstream& is, User& obj);
	friend ostream& operator <<(ostream& os, const User& obj);


};

fstream& operator >>(fstream& is, User& obj)
{

	is >> obj._name;
	is >> obj._login;
	is >> obj._pass;
	return is;
}
ostream& operator <<(ostream& os, const User& obj)
{

	os << obj._name;
	os << ' ';
	os << obj._login;
	os << ' ';
	os << obj._pass;
	return os;
}


class Message {
public:
	string _text;
	string _sender;
	string _receiver;


	Message(string text, string sender, string receiver) : _text(text), _sender(sender), _receiver(receiver) {
		replace_all(_text, " ", "_");
	}

	Message() {
		_text = "";
		_sender = "";
		_receiver = "";
	}

	const string& GetMessageText() {
		string to_return = _text;
		replace_all(to_return, "_", " ");
		return to_return;
	}

	friend fstream& operator >>(fstream& is, Message& obj);
	friend ostream& operator <<(ostream& os, const Message& obj);
};

fstream& operator >>(fstream& is, Message& obj)
{

	is >> obj._text;
	is >> obj._sender;
	is >> obj._receiver;
	return is;
}
ostream& operator <<(ostream& os, const Message& obj)
{
	os << obj._text;
	os << " ";
	os << obj._sender;
	os << " ";
	os << obj._receiver;
	return os;
}


User& extractUser()
{
	fstream user_file = fstream("users.txt", ios::in | ios::out);
	if (!user_file) {
		user_file = fstream("users.txt", ios::in | ios::out | ios::trunc);
		setOwnerPermissions("users.txt");
	}


	if (user_file) {
		User obj;
		user_file.seekg(0, ios_base::beg);
		// Считываем данные из файла
		user_file >> obj;
		return obj;
	}
	else
	{
		cout << "Could not open file users.txt !" << '\n';
	}
}

void insertUser(User& obj) {
	fstream user_file = fstream("users.txt", ios::in | ios::out);
	if (!user_file){ 
		user_file = fstream("users.txt", ios::in | ios::out | ios::trunc);
		setOwnerPermissions("users.txt"); }

	if (user_file) {

		user_file.seekg(0, ios_base::beg);
		user_file << obj << endl;

	}
	else
	{
		cout << "Could not open file users.txt !" << '\n';

	}
}


Message& extractMessage()
{
	fstream message_file = fstream("messages.txt", ios::in | ios::out);
	if (!message_file) {
		message_file = fstream("messages.txt", ios::in | ios::out | ios::trunc);
		setOwnerPermissions("messages.txt");
	}
		// Для создания файла используем параметр ios::trunc
		

	if (message_file) {
		Message obj;
		message_file.seekg(0, ios_base::beg);
		// Считываем данные из файла
		message_file >> obj;
		return obj;
	}
	else
	{
		cout << "Could not open file messages.txt !" << '\n';
	}
}

void insertMessagee(Message& obj) {
	fstream message_file = fstream("messages.txt", ios::in | ios::out);
	if (!message_file) {
		message_file = fstream("messages.txt", ios::in | ios::out | ios::trunc);
		setOwnerPermissions("messages.txt");
	}

	if (message_file) {

		message_file.seekg(0, ios_base::beg);
		message_file << obj << endl;

	}
	else
	{
		cout << "Could not open file messages.txt !" << '\n';

	}
}

int main() {
	User obj;
	Message mes("hi there im using Linux", "me", "you");
	insertMessagee(mes); // сохранение состояния
	extractMessage(); // извлечение состояния

	insertUser(obj);
	extractUser();

}


