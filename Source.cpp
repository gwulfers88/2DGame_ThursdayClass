#include <string>
#include <vector>
#include <iostream>

enum Key {
	U, D, L, R, // up, down, left, right
	P,	// punch
	K	// kick
};

typedef std::vector<Key> Keys;
typedef std::pair<Keys, std::string> MoveToAction;
typedef std::vector<MoveToAction> Moveset;

// imperfect input matching
bool match(const Keys& input, const Keys& move, int threshold = 1)
{
	// not enough keys to do move
	int input_size = input.size();
	int move_size = move.size();

	if (input_size < move_size)
		return false;

	int mismatch = 0;

	int j = input_size - 1; 
	int i = move_size - 1;

	// Very latest input must match
	if (input[j] != move[i])
		return false;

	for (; i >= 0 && j >= 0; --j)
	{
		if (input[j] != move[i]) {
			++mismatch;
		}
		else
		{
			mismatch = 0;
			--i;
		}

		if (mismatch >= threshold)
			return false;
	}
	return j >= 0;
}

// perfect input matching
/*bool match(const Keys& input, const Keys& move)
{
	// not enough keys to do move
	int input_size = input.size();
	int move_size = move.size();

	if (input_size < move_size)
		return false;

	int j = input_size - 1;
	for (int i = move_size - 1; i >= 0; --i, --j)
	{
		if (input[j] != move[i])
			return false;
	}
	return true;	
}*/

int main()
{
	const Keys r_dragonpunch = { R, D, R, P }; 
	const Keys r_fireball = { D, R, P };
	const Keys r_hurricanekick = { D, R, K };

	const Moveset moveset = { 
		MoveToAction(r_dragonpunch, "SHOYUUUUKEN!!") ,
		MoveToAction(r_fireball, "HADOOOOOKEN!!") ,
		MoveToAction(r_hurricanekick, "I'D LIKE SOME POUND CAKE!!")
	};

	Keys input_history;

	char input;
	do {
		std::cin >> input;

		switch (input) 
		{
		case 'w':
			input_history.push_back(Key::U);
			break;
		case 'a':
			input_history.push_back(Key::L);
			break;
		case 's':
			input_history.push_back(Key::D);
			break;
		case 'd':
			input_history.push_back(Key::R);
			break;
		case 'p':
			input_history.push_back(Key::P);
			break;
		case 'k':
			input_history.push_back(Key::K);
			break;
		}

	} while (input != '0');


	for (const MoveToAction& moveToAction : moveset) {
		const Keys& move = moveToAction.first;
		const std::string& action = moveToAction.second;

		if (match(input_history, move, 4)) {
			std::cout << action << std::endl;
			break;
		}
	}
	/*if (match(input_history, r_dragonpunch, 1)) {
		std::cout << "SHOYUUUUKEN!!" << std::endl;
	}
	else if (match(input_history, r_fireball, 1)) {
		std::cout << "HADOOOOOKEN!!" << std::endl;
	}
	else if (match(input_history, r_hurricanekick)) {
		std::cout << "I'D LIKE SOME POUND CAKE!!" << std::endl;
	}*/

	return 0;
}