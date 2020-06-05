#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <windows.h>
#include <sstream>
#include <list>
#include <sstream>
using namespace std;
using namespace sf;
typedef enum skill_number {
	kill,             // kill
	jink,             // escape
	analeptic,        // wine
	peach             // peach
};
typedef enum game_state {
	zhugong_win,
	fanzei_win,
	neijing_win
};
typedef enum extra_turn {
	normal,            // normal turn 
	human,
	machine_0,
	machine_1,
	machine_2,
	machine_3
};

typedef struct Card_Info {
	int single_card_number;     // ��������Ӧ���ƺ�
	/**---->>>>suit
	 * ��ɫ 0,1,2,3 �ֱ���� ���ң�Spade�������ң�Heart�������飨Diamond����÷����Club��
	 */
	int suit;
	bool can_attck;             // whether it can choose enemy
};
typedef struct Single_Card {  // each card property
	Card_Info card_info;        // �������� �ƺ�&��ɫ
	bool mouse_select_card;     // gameround a flag to show whether the card is selected
	bool file_loaded;           // flag to judge whether the image has been loaded from file ( to escape R&W to increase game speed)
	bool own_card;              // �Ƿ��������
	bool enable_to_play;        // �Ƿ�ɳ���
	bool text;
	string card_name;           // ���Ƶ�����
	Texture texture_card;
	Sprite sprite_card;
	// get card position
	Vector2i point_one;
	Vector2i point_two;
	Single_Card* next;
}Single_Card, * LinkList;

typedef struct Message {  // message box
	char text[100];
	Message* next;
}Message, * Message_Box;

class Button
{
public:
	bool is_disabled;
	bool is_normal;
	bool is_hover;
	bool is_down;
	void enable_diabled_button() {
		is_disabled = true;
		is_normal = false;
		is_hover = false;
		is_down = false;
	}
	void enable_hover_button() {
		is_disabled = false;
		is_normal = false;
		is_hover = true;
		is_down = false;
	}
	void enable_normal_button() {
		is_disabled = false;
		is_normal = true;
		is_hover = false;
		is_down = false;
	}
	void enable_down_button() {
		is_disabled = false;
		is_normal = false;
		is_hover = false;
		is_down = true;
	}
	Texture texture_disabled, texture_normal, texture_hover, texture_down;
	Sprite sprite_disabled, sprite_normal, sprite_hover, sprite_down;
	Button() {
		is_disabled = false;
		is_normal = false;
		is_hover = false;
		is_down = false;
	}
};

class Pile_Card {
public:
	LinkList Pile_Card_Total;          // LinkList
	int Pile_Card_Amount;              // the total number of pile card
	void Insert_Card(int number, int _suit) {
		//β�巨 ���� ���
		LinkList S = new Single_Card;
		S->next = NULL;
		//��ֵ
		S->card_info.single_card_number = number;
		S->card_info.suit = _suit;
		S->card_info.can_attck = Card_Can_Attack(number);
		S->file_loaded = false;
		LinkList P = Pile_Card_Total;
		while (P->next)
			P = P->next;  // find tail node
		Pile_Card_Amount++;
		P->next = S;
		P = S;
		cout << "***********yes get card succeed!!!" << endl;
	}
	bool Delete_Card(int number) {
		LinkList T = Pile_Card_Total;
		while (T->next) {
			if (T->next->card_info.single_card_number == number) {
				LinkList p = T->next;
				T->next = p->next;
				Pile_Card_Amount--;
				delete p;
				cout << "<<<<delete card succeed!!!" << endl;
				return true;
			}
			else T = T->next;
		}
		return false;
	}
	bool Detete_Card_Selected() {
		LinkList T = Pile_Card_Total;
		while (T->next) {
			if (T->next->mouse_select_card == true) {
				LinkList p = T->next;
				T->next = p->next;
				Pile_Card_Amount--;
				delete p;
				cout << "<<<<delete card succeed!!!" << endl;
				return true;
			}
			else T = T->next;
		}
		return false;
	}
	void Bubblesort_Card() {
		Single_Card* pre, * p, * tail;
		tail = NULL;
		while (Pile_Card_Total->next != tail)
		{
			pre = Pile_Card_Total;
			p = Pile_Card_Total->next;
			while (p->next != tail)
			{
				if (p->card_info.single_card_number > p->next->card_info.single_card_number)
				{
					pre->next = p->next;
					p->next = pre->next->next;
					pre->next->next = p;
				}
				else
					p = p->next;
				pre = pre->next;
			}
			tail = p;
		}
		cout << "bubble sort succeed!!!" << endl;
	}
	bool Search_Card(int value) {
		Single_Card* ptr = Pile_Card_Total->next;
		if (ptr == NULL) {
			cout << "the linklist is null,not found!!!" << endl;
			return false;
		}
		while (ptr != NULL && ptr->card_info.single_card_number != value) { ptr = ptr->next; }
		if (ptr != NULL) {
			cout << "find!>>" << value << endl;
			return true;
		}
		else {
			cout << "NOT-FOUND__XXXXX>>" << value << endl;
			return false;
		}
	}
	bool Card_Can_Attack(int number) {
		switch (number)
		{
		case kill: return true;
		default: return false;
		}
	}
	bool Search_Card_Position(Vector2i target_position) {
		Single_Card* ptr = Pile_Card_Total->next;
		if (ptr == NULL) {
			cout << "the linklist is null,not found!!!" << endl;
			return false;
		}
		while (ptr != NULL && !((target_position.x >= ptr->point_one.x) && (target_position.x <= ptr->point_two.x) && (target_position.y >= ptr->point_one.y) && (target_position.y <= ptr->point_two.y))) { ptr = ptr->next; }
		if (ptr != NULL) {
			cout << "find that! " << "mouse_X" << target_position.x << "||mouse_Y" << target_position.y << endl;
			return true;
		}
		else {
			return false;
		}
	}

	Single_Card* Search_Card_Position_locate(Vector2i target_position) {
		Single_Card* ptr = Pile_Card_Total->next;
		if (ptr == NULL) {
			cout << "the linklist is null,not found!!!" << endl;
		}
		while (ptr != NULL && !((target_position.x >= ptr->point_one.x) && (target_position.x <= ptr->point_two.x) && (target_position.y >= ptr->point_one.y) && (target_position.y <= ptr->point_two.y))) { ptr = ptr->next; }
		if (ptr != NULL) {
			cout << "find that! " << "mouse_X" << target_position.x << "||mouse_Y" << target_position.y << endl;
			return ptr;
		}
		else {
			cout << "target search false! no such one!>>>>>>> " << "mouse_X" << target_position.x << "||mouse_Y" << target_position.y << endl;
		}
	}
	void Change_number_to_name() {
		Single_Card* ptr = Pile_Card_Total->next;
		while (ptr != NULL)
		{
			switch (ptr->card_info.single_card_number)
			{
			case 0:  // kill
				ptr->card_name = "ɱ";
				break;
			case 1:  // jink
				ptr->card_name = "��";
				break;
			case 2:  //
				ptr->card_name = "��";
				break;
			case 3:
				ptr->card_name = "��";
				break;
			case 4:
				ptr->card_name = "444";
				break;
			case 5:
				ptr->card_name = "555";
				break;
			case 6:
				ptr->card_name = "666";
				break;
			case 7:
				ptr->card_name = "777";
				break;
			case 8:
				ptr->card_name = "888";
				break;
			default:
				break;
			}
			ptr = ptr->next;
		}
	}
	void Shuffle_Card() {
		srand(time(NULL));
		for (int i = 0; i < 200; i++)
		{
			Insert_Card((rand() % 4), (rand() % 4));
		}
		Change_number_to_name();
	}
	Single_Card* Get_Node(int order) { // get No.i node
		Single_Card* ptr = Pile_Card_Total->next;
		for (int i = 0; i < order; i++) { ptr = ptr->next; }
		return ptr;
	}
	Pile_Card() {
		Pile_Card_Total = new Single_Card;
		Pile_Card_Total->next = NULL;
		Pile_Card_Amount = 0;
	}
};

class Skill
{
public:
	bool need_jink;            // set a state when someone play kill or other skill that need jink , target need play jink
	bool need_kill;            // also
	bool receive_peach;
	bool need_analeptic;
	bool begging_peach;
	bool defense_analeptic_kill;
	bool have_decide_saving;
	// define skill 

	Skill() {
		need_jink = false;
		need_kill = false;
		receive_peach = false;
		need_analeptic = false;
		begging_peach = false;
		defense_analeptic_kill = false;
		have_decide_saving=false;
	}
};

class Player
{
public:
	int charactor_code;         // code for player object
	Vector2i location_one;    // in order to locate machine's position--Upper left corner
	Vector2i location_two;    // in order to locate machine's position--Lower right corner
	bool is_Mechine;            // �ж϶����� �� ���� ����
	int HP;                     // the amount of blood
	int limited_HP;             // the limited of blood , influenced by role player get
	bool is_dying;              // whether play have been in dying state
	bool die;                   // whether player is die assure
	bool self_save;             // about save themselves
	//int target;                 // ��ӦĿ�� ������Ϊ0��˳ʱ��++
	bool being_choose;          // being a target to others
	int kill_power;             // the damage that player use kill && normally the value is 1
	int kill_limit;             // the limit number that player use kill && normally is 1
	int kill_times;
	bool drank_analeptic;        // judge whether it played analeptic

	// emery can choose
	int chosen_number;

	/**
	 * ɱ�Ĺ���������1,����ɱ�����������ߵ����,װ�������Ļ����Ͱ�����������Χ
	 * ���㡣���Ӳ���,�ֲ�˼��û�о������ơ���˳��ǣ��,������ϵľ�����1��+1��
	 * ����װ��֮��,������Һ���֮��ľ���+1,���ڵ��������ľ���Ϊ2,�������
	 * �ľ���Ϊ1,+1�����������������룬�ñ����Ҵ򲻵��㡣-1��,����ͱ����
	 * �Ҽ������ʱ-1,Ҳ������û������Ҳ��ɱ������Ϊ2���ˡ�
	 */
	int distance;               // ���������־��룬������װ��
	Pile_Card cards;            // ��Ҷ������е� �ƶ� ����
	bool have_horse;            // �����û����
	bool have_weapon;           // �����û��װ��
	bool have_armor;            // �����û�з���
	bool round_draw_phase;      // �غϿ�ʼ���ƽ׶�
	bool round_play_phase;      // a signal to judge whether it can play or not
	bool round_discard_phase;   // a signal to judge whether this round have been over
	bool select_card;           // each time a player can only select one card to play
	int selecet_card_amount;    // when discard,it can calculate discard amount
	bool animator_kill, animator_jink, animator_peach, animator_analeptic, animator_damage;                   // bool to constrain animator of kill
	int animator_kill_counter, animator_jink_counter, animator_peach_counter, animator_analeptic_counter, animator_damage_counter;            // counter to remember each texture

	// for dying to beg peach
	Texture texture_sos_phase;
	Sprite sprite_sos_phase;
	// for draw phase
	Texture texture_draw_phase;
	Sprite sprite_draw_phase;
	// for play phase
	Texture texture_play_phase;
	Sprite sprite_play_phase;
	// for discard phase
	Texture texture_discard_phase;
	Sprite sprite_discard_phase;
	// for judge phase
	Texture texture_judge_phase;
	Sprite sprite_judge_phase;
	// for response phase
	Texture texture_response_phase;
	Sprite sprite_response_phase;

	Skill skill;

	// initialize player's life & other original set
	Player() { 
		// basic character value
		charactor_code = -1;
		HP = 1; 
		limited_HP = HP; 
		kill_power = 1; 
		kill_limit = 1; 
		selecet_card_amount = 0; 
		select_card = false; 
		drank_analeptic = false; 
		die = false; 
		is_dying = false; 
		skill.begging_peach = false; 
		// basic game state
		round_draw_phase = false;
		round_play_phase = false;
		round_discard_phase = false;
		// chosen 
		chosen_number = 0;
	}
};

