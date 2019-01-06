#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print_vector(vector<int> print) {
	cout << " [ ";
	for (int i = 0; i < print.size(); i++) {
		cout << print[i];
		if (i < print.size() - 1) {
			cout << " , ";
		}
	}
	cout << " ] " << endl;
}

vector<int> reverse_vector(vector<int> initial) {
	vector<int> reversed;
	for (int i = 0; i < initial.size(); i++) {
		int current = initial[initial.size() - 1 - i];
		reversed.push_back(current);
	}
	return reversed;
}


vector<int> convert_input(string raw) {
	vector <int> deck;
	string current;
	for (int i = 0; i < raw.size(); i++) {
		if (raw[i] != ' ') {
			if (raw[i] == ',') {
				deck.push_back(stoi(current));
				current = "";
			}
			else {
				switch (raw[i]) {
				case ('T'):
					current += "10";
					break;
				case ('J'):
					current += "11";
					break;
				case ('Q'):
					current += "12";
					break;
				case ('K'):
					current += "13";
					break;
				case ('A'):
					current += "14";
					break;
				default:
					current += raw[i];
				}
			}
		}
	}
	deck.push_back(stoi(current));
	deck = reverse_vector(deck);
	cout << "Reversed Deck:";
	print_vector(deck);
	return deck;
}

int add_Card_Value(int value, int score) {
	switch (value) {
	case (9):
		return 0;
	case (10):
		return -10;
	case (14):
		if (14 + score > 99) {
			return 1;
		}
		else {
			return 14;
		}
	default:
		return value;
	}
}

void play_Card(bool& player_turn, int& score, vector<int>& deck, vector<int>& player_deck) {
	int card_value = 0;
	if (player_turn) {
		int largest = 0;
		int largest_i = 0;
		for (int i = 0; i < 3; i++) {
			if (player_deck[i] > largest) {
				largest = player_deck[i];
				largest_i = i;
			}
		}
		player_deck.erase(player_deck.begin() + largest_i);
		card_value = largest;
		player_deck.push_back(deck.back());
	}
	else {
		card_value = deck.back();
	}
	deck.pop_back();
	int added_value = add_Card_Value(card_value, score);
	score += added_value;
	cout << "Score Change: " << added_value << endl;
}

void start_Game(int& score, vector<int>& deck, vector<int>& player_deck) {
	string winner;
	bool player_turn = true;
	cout << endl << "New Game!" << endl;
	cout << "Starting Deck:";
	print_vector(deck);
	cout << "Starting Player Deck:";
	print_vector(player_deck);
	cout << "Starting Score: " << score << endl << endl;

	while (score <= 99) {
		cout << "Player Turn: " << player_turn << endl;
		play_Card(player_turn, score, deck, player_deck);
		cout << "Current Deck: ";
		print_vector(deck);
		cout << "Current Player Deck: ";
		print_vector(player_deck);
		cout << "New Score: " << score << endl << endl;
		player_turn = !player_turn;
	}

	if (player_turn) {
		winner = "player";
	}
	else {
		winner = "dealer";
	}

	cout << "Game Over!" << endl;
	cout << score << ", " << winner << endl;
}


int main() {
	while (true) {
		int score;
		string input_raw;
		vector <int> deck;
		vector <int> player_deck;
		cout << "ACSL Ninety-Nine C++" << endl << endl;
		cout << "Enter Input (or 'exit' to exit):" << endl;
		getline(cin, input_raw);
		if (input_raw == "exit") {
			break;
		}
		cout << "\n" << "You Entered: " << input_raw << endl;
		deck = convert_input(input_raw);
		score = deck.back();
		deck.pop_back();
		for (int i = 0; i < 3; i++) {
			player_deck.push_back(deck.back());
			deck.pop_back();
		}

		start_Game(score, deck, player_deck);
		cout << endl << endl << endl;
	}
	return 0;
}