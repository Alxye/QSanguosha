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

LPCWSTR string_To_LPCWSTR(string _string) {
	size_t origsize = _string.length() + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* _LPCWSTR = (wchar_t*)malloc(sizeof(wchar_t) * (_string.length() - 1));
	mbstowcs_s(&convertedChars, _LPCWSTR, origsize, _string.c_str(), _TRUNCATE);
	return _LPCWSTR;
}
// load image
void Load_Image(Texture& texture, Sprite& sprite, string filename, float originX=0, float originY=0, float factorX=1, float factorY=1) {
	if (!texture.loadFromFile(filename)) {
		int result = MessageBox(NULL, string_To_LPCWSTR("Invalid Path , image is missing : " + filename), TEXT("Error ! Failed to load !"), MB_RETRYCANCEL);
		switch (result) {
		case IDRETRY:
			return Load_Image(texture, sprite, filename, originX, originY, factorX, factorY);
		case IDCANCEL:
			exit(0);
		}
	}
	else {
		cout << "贴图加载成功" << endl;
		sprite.setTexture(texture);
		sprite.setOrigin(originX, originY);
		sprite.setScale(factorX, factorY);
	}
}
typedef struct Card_Info {
	int single_card_number;     // 该牌所对应的牌号
	/**---->>>>suit
     * 花色 0,1,2,3 分别代表 黑桃（Spade）、红桃（Heart）、方块（Diamond）、梅花（Club）
     */
	int suit;
	bool can_attck;             // whether it can choose enemy
};
typedef struct Single_Card {  // each card property
	Card_Info card_info;        // 卡的属性 牌号&花色
	bool mouse_select_card;     // gameround a flag to show whether the card is selected
	bool file_loaded;           // flag to judge whether the image has been loaded from file ( to escape R&W to increase game speed)
	bool own_card;              // 是否被玩家所有
	bool enable;                // 是否可出牌
	bool text;
	string card_name;           // 该牌的名字
	Texture texture_card;
	Sprite sprite_card;
	// get card position
	Vector2i point_one;
	Vector2i point_two;
	Single_Card* next;
}Single_Card, * LinkList;

class Button
{
public:
	bool is_disabled;
	bool is_normal;
	bool is_hover;
	bool is_down;
	void enable_diabled_button() {
		is_disabled = true;
		is_normal=false;
		is_hover=false;
		is_down=false;
	}
	void enable_hover_button() {
		is_disabled = false;
		is_normal=false;
		is_hover=true;
		is_down=false;
	}
	void enable_normal_button() {
		is_disabled = false;
		is_normal=true;
		is_hover=false;
		is_down=false;
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
	LinkList Pile_Card_Total;          /*链表*/
	int Pile_Card_Amount;              //牌堆中 牌数
	void Insert_Card(int number, int _suit) {
		//尾插法 新增 结点
		LinkList S = new Single_Card;
		S->next = NULL;
		//赋值
		S->card_info.single_card_number = number;
		S->card_info.suit = _suit;
		S->card_info.can_attck = Card_Can_Attack(number);
		S->file_loaded = false;
    	LinkList P = Pile_Card_Total;
		while (P->next)
			P = P->next;/*找到链表队尾指针*/
		Pile_Card_Amount++;
		P->next = S;
		P = S; /*尾插法*/
		cout << "***********加牌成功 得到牌了！！！" << endl;
	}
	bool Delete_Card(int number) {
		LinkList T = Pile_Card_Total;
		while (T->next) {
			//cout << T->next->card_name << endl;
			//cout << name << endl;
			if (T->next->card_info.single_card_number == number) {
				LinkList p = T->next;
				T->next = p->next;
				Pile_Card_Amount--;
				delete p;
				cout << "<<<<抽牌/出牌成功" << endl;
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
		cout << "排序成功" << endl;
	}
	bool Search_Card(int value) {
		Single_Card* ptr = Pile_Card_Total->next;
		if (ptr == NULL) {
			printf_s("链表&卡牌为空\n");
			return false;
		}
		while (ptr != NULL && ptr->card_info.single_card_number != value) { ptr = ptr->next; }
		if (ptr != NULL) {
			printf_s("找到 %d 了\n", value);
			return true;
		}
		else {
			printf_s("没有找到 %d\n", value);
			return false;
		}
	}
	bool Card_Can_Attack(int number) {
		switch (number)
		{
		case 0: return true;
		default: return false;
		}
	}
	bool Search_Card_Position(Vector2i target_position) {
		Single_Card* ptr = Pile_Card_Total->next;
		if (ptr == NULL) {
			printf_s("链表&卡牌为空\n");
			return false;
		}
		while (ptr != NULL && !((target_position.x >= ptr->point_one.x) && (target_position.x <= ptr->point_two.x) && (target_position.y >= ptr->point_one.y) && (target_position.y <= ptr->point_two.y))) { ptr = ptr->next; }
		if (ptr != NULL) {
			cout << "find that! " << "mouse_X" << target_position.x << "||mouse_Y" << target_position.y << endl;
			return true;
		}
		else {
			//cout << "target search false! no such one!>>>>>>> " << "mouse_X" << target_position.x << "||mouse_Y" << target_position.y << endl;
			return false;
		}
	}

	Single_Card * Search_Card_Position_locate(Vector2i target_position) {
		Single_Card* ptr = Pile_Card_Total->next;
		if (ptr == NULL) {
			printf_s("链表&卡牌为空\n");
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
			case 0:
				ptr->card_name = "杀";
				break;
			case 1:
				ptr->card_name = "闪";
				break;
			case 2:
				ptr->card_name = "酒";
				break;
			case 3:
				ptr->card_name = "桃";
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


class Player
{
public:
	bool is_Mechine;            // 判断对象是 人 还是 机器
	int HP;                     // the amount of blood
	int target;                 // 对应目标 对象本身为0；顺时针++
	bool being_choose;          // being a target to others
	/**
	 * 杀的攻击距离是1,可以杀到你左右两边的玩家,装上武器的话，就按武器攻击范围
	 * 计算。过河拆桥,乐不思蜀没有距离限制。而顺手牵羊,兵粮寸断的距离是1。+1马
	 * 是你装备之后,其他玩家和你之间的距离+1,相邻的玩家与你的距离为2,而你和他
	 * 的距离为1,+1马的意义就是拉开距离，让别的玩家打不到你。-1马,是你和别的玩
	 * 家计算距离时-1,也就是你没有武器也能杀到距离为2的人。
	 */
	int distance;               // 和其他对手距离，比如马、装备
	Pile_Card cards;            // 玩家对象所有的 牌堆 对象
	bool have_horse;            // 玩家有没有马
	bool have_weapon;           // 玩家有没有装备
	bool have_armor;            // 玩家有没有防具
	bool round_draw_phase;      // 回合开始摸牌阶段
	bool round_play_phase;      // a signal to judge whether it can play or not
	bool select_card;           // each time a player can only select one card to play
	int button_assure;          // there exist four stage : unable;normal;hover;click
	int button_cancel;          // there exist four stage : unable;normal;hover;click
	int button_over;            // there exist four stage : unable;normal;hover;click

	//定义游玩者
	Player() { HP = 4; }
};

class Skill
{
public:
	// define skill 
	void kill(Player player, Player target) {
		//cout << "what fuck!" << endl;
		//if (enemy.play_card(enemy.play_card())) {
			// 			return;
		//}
		cout << "666" << endl;
		//}
	}
	Skill() {}
};

class Game
{
public:
	RenderWindow window;
	int window_width, window_height;
	int turn;                             // 轮到谁的 记录量
	bool gamestart, gameover, gamequit;
	bool new_round;
	Event event_global;
	Pile_Card piles;
	Player Human, Machine;
	Vector2i mouse_count_clock_one, mouse_count_clock_two;
	Clock mouse_click_timer;
	// for stable background
	Texture texture_background, texture_player_equip_board, texture_player_hand_board, texture_player_button_background, texture_player_role_background, texture_npcboard, texture_npc_cards, texture_piles_back;
	Sprite sprite_background, sprite_player_equip_board, sprite_player_hand_board, sprite_player_button_background, sprite_player_role_background, sprite_npcboard, sprite_npc_cards, sprite_piles_back;
	// for npc
	Texture texture_being_chosen;
	Sprite sprite_being_chosen;
	// for button
	Button button_cancel, button_discard, button_ok;
	//游戏 类的实现
	void Initial() {
		// initialize game state
		gamestart = true;
		gameover = false;
		gamequit = false;
		new_round = true;
		// initialize round state
		Machine.round_draw_phase = false;
		Human.round_draw_phase = false;
		// get cards shuffled
		piles.Shuffle_Card();
		Load_Image(texture_background, sprite_background, "image/back_stable/background.jpg", 0, 0, 1, 1); // 加载背景
		Load_Image(texture_player_equip_board, sprite_player_equip_board, "image/back_stable/playerboard-equip.png");
		Load_Image(texture_player_hand_board, sprite_player_hand_board, "image/back_stable/playerboard-hand.png");
		Load_Image(texture_player_button_background, sprite_player_button_background, "image/back_stable/playerbutton_background.png");
		Load_Image(texture_npcboard, sprite_npcboard, "image/back_stable/npcboard.png");
		Load_Image(texture_npc_cards, sprite_npc_cards, "image/back_stable/handcard.png");
		Load_Image(texture_player_role_background, sprite_player_role_background, "image/back_stable/playerboard-role.png");
		Load_Image(texture_piles_back, sprite_piles_back, "image/back_stable/pile_back.png");
		// load npc_being chosen
		Load_Image(texture_being_chosen, sprite_being_chosen, "image/back_stable/sos.png", 0, 0, 1, 1);
		// load button 
		//---->> cancel button
		Load_Image(button_cancel.texture_disabled,button_cancel.sprite_disabled, "image/back_stable/button/cancel-disabled.png", 0, 0, 1, 1);
		Load_Image(button_cancel.texture_down,button_cancel.sprite_down, "image/back_stable/button/cancel-down.png", 0, 0, 1, 1);
		Load_Image(button_cancel.texture_hover,button_cancel.sprite_hover, "image/back_stable/button/cancel-hover.png", 0, 0, 1, 1);
		Load_Image(button_cancel.texture_normal,button_cancel.sprite_normal, "image/back_stable/button/cancel-normal.png", 0, 0, 1, 1);
		//---->> discard button
		Load_Image(button_discard.texture_disabled, button_discard.sprite_disabled, "image/back_stable/button/discard-disabled.png", 0, 0, 1, 1);
		Load_Image(button_discard.texture_down, button_discard.sprite_down, "image/back_stable/button/discard-down.png", 0, 0, 1, 1);
		Load_Image(button_discard.texture_hover, button_discard.sprite_hover, "image/back_stable/button/discard-hover.png", 0, 0, 1, 1);
		Load_Image(button_discard.texture_normal, button_discard.sprite_normal, "image/back_stable/button/discard-normal.png", 0, 0, 1, 1);
		//---->> assure button
		Load_Image(button_ok.texture_disabled, button_ok.sprite_disabled, "image/back_stable/button/ok-disabled.png", 0, 0, 1, 1);
		Load_Image(button_ok.texture_down, button_ok.sprite_down, "image/back_stable/button/ok-down.png", 0, 0, 1, 1);
		Load_Image(button_ok.texture_hover, button_ok.sprite_hover, "image/back_stable/button/ok-hover.png", 0, 0, 1, 1);
		Load_Image(button_ok.texture_normal, button_ok.sprite_normal, "image/back_stable/button/ok-normal.png", 0, 0, 1, 1);
		

		turn = Previous_Draw_Phase();            // first round is effected in initial function , then it goes a loop
	}

	Vector2i Input() {
		//Event event_global;
		while (window.pollEvent(event_global)) {
			if (event_global.type == Event::Closed) {
				window.close();
				gamequit = true;
			}
			if (Human.round_play_phase){
				if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
					cout << "进来了，啊？" << endl;
					mouse_count_clock_two = Mouse::getPosition(window);
					if (mouse_click_timer.getElapsedTime().asMilliseconds() < 500 && mouse_count_clock_two.x - mouse_count_clock_one.x < 10 && mouse_count_clock_two.y - mouse_count_clock_one.y < 10) {
						cout << "Mouse::Left double click" << endl;
						cout << mouse_count_clock_two.x << " || " << mouse_count_clock_two.y<<endl;
						return mouse_count_clock_two;
					}
					else{
						cout << "Mouse::Left click" << endl;
						cout << mouse_count_clock_two.x << " || " << mouse_count_clock_two.y << endl;
						return mouse_count_clock_two; 
					}
				}
				if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
					mouse_count_clock_one = Mouse::getPosition(window);
					//bool card_selected = Human.cards.Search_Card_Position(mouse_count_clock_one);
					mouse_click_timer.restart();
					cout << "Mouse::Left Release" << endl;
					cout << " released:mouse_two:" << mouse_count_clock_two.x << " || " << mouse_count_clock_two.y << endl;
					cout <<" released:mouse_one:" <<mouse_count_clock_one.x << " || " << mouse_count_clock_one.y << endl;

					//return mouse_count_clock_one;
				}
				
				if (event_global.type == sf::Event::MouseMoved)
				{
					// control button of cancel in hover state
					if (!button_cancel.is_disabled) {
						if (event_global.mouseMove.x > 807 && event_global.mouseMove.x < (807 + 61) && event_global.mouseMove.y > 694 && event_global.mouseMove.y < (694 + 73))
						{ // the button of cancel //(807, 694)++(61,73)
							cout << "new mouse x: " << event_global.mouseMove.x << endl;
							cout << "new mouse y: " << event_global.mouseMove.y << endl;
							button_cancel.enable_hover_button();
							cout << "鼠标位于取消上" << endl;
						}
						else{
							cout << "new mouse x: " << event_global.mouseMove.x << endl;
							cout << "new mouse y: " << event_global.mouseMove.y << endl;
							button_cancel.enable_normal_button();
							cout << "鼠标不在取消上" << endl;
						}
					}
					// control button of assure
					if (!button_ok.is_disabled) {
						if (event_global.mouseMove.x > 807 && event_global.mouseMove.x < (807 + 61) && event_global.mouseMove.y > 604 && event_global.mouseMove.y < (604 + 75))
						{ // the button of ok //(807, 604)++(61,75)
							cout << "new mouse x: " << event_global.mouseMove.x << endl;
							cout << "new mouse y: " << event_global.mouseMove.y << endl;
							button_ok.enable_hover_button();
							cout << "鼠标位于确定上" << endl;
						}
						else{
							cout << "new mouse x: " << event_global.mouseMove.x << endl;
							cout << "new mouse y: " << event_global.mouseMove.y << endl;
							button_ok.enable_normal_button();
							cout << "鼠标不在确定上" << endl;
						}
					}
					// control button of discard in hover state
					if (!button_discard.is_disabled) {
						if (event_global.mouseMove.x > 874 && event_global.mouseMove.x < (874 + 33) && event_global.mouseMove.y > 644 && event_global.mouseMove.y < (644 + 81))
						{ // the button of ok //(874, 644)++(33,81)
							cout << "new mouse x: " << event_global.mouseMove.x << endl;
							cout << "new mouse y: " << event_global.mouseMove.y << endl;
							button_discard.enable_hover_button();
							cout << "鼠标位于结束上" << endl;
						}
						else{
							cout << "new mouse x: " << event_global.mouseMove.x << endl;
							cout << "new mouse y: " << event_global.mouseMove.y << endl;
							button_discard.enable_normal_button();
							cout << "鼠标不在结束上" << endl;
						}
					}
				}
			}
		}
	}

	int Previous_Draw_Phase() {
		// machine get 4 cards
		for (int i = 0; i < 4; i++) {
			Machine.cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
			piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
		}
		// human get 4 cards
		for (int i = 0; i < 4; i++) {
			Human.cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
			Human.cards.Get_Node(Human.cards.Pile_Card_Amount - 1)->mouse_select_card = false;
			piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
		}
		//return rand() % 2;  // the rand function would detenmine which one to play first
		return 1;
	}
	void Round_Initialize(int turn) { // about turn :  0——machine || 1——Human player
		if (turn == 0) {  // machine's round
			Machine.round_draw_phase = true;
		}
		else if (turn == 1) { // humans round
			Human.round_draw_phase = true;
			Human.round_play_phase = true;
		}
		new_round = false;
	}
	void Human_Round() {
		Vector2i mouse_select_vector = Input();  // in general there only exist one input function  * wtf! that is matter most
		if (piles.Pile_Card_Amount < 20) piles.Shuffle_Card(); // if card few ,shuffle
		// human get 2 cards each time is its round
		if (Human.round_draw_phase) {
			for (int i = 0; i < 2; i++) {
				Human.cards.Insert_Card(piles.Pile_Card_Total->next->card_info.single_card_number, piles.Pile_Card_Total->next->card_info.suit);
				Human.cards.Get_Node(Human.cards.Pile_Card_Amount - 1)->mouse_select_card = false;
				piles.Delete_Card(piles.Pile_Card_Total->next->card_info.single_card_number);
			}
			Human.round_draw_phase = false;
		}
		// to update player's card with card_texture,card_sprite,card_vector;
		Single_Card* ptr = Human.cards.Pile_Card_Total->next;
		for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
			if (!ptr->file_loaded) {
				stringstream ss;
				ss << "image/skill&equip_card/small_card/" << ptr->card_info.single_card_number << ".jpg";
				Load_Image(ptr->texture_card, ptr->sprite_card, ss.str(), 0, 0, 1, 1);
				ptr->file_loaded = true;
			}
			ptr = ptr->next;
		}
		if (Human.round_play_phase) {
			// button stage initialize
			if ((Human.select_card == false)&&!(button_discard.is_hover)){ // there exist tow kind of situation -- original initialize and no hover
				button_ok.enable_diabled_button();
				button_cancel.enable_diabled_button();
				button_discard.enable_normal_button();
			}
			//cout << mouse_select_vector.x << " || " << mouse_select_vector.y << endl;
			if (Human.cards.Search_Card_Position(mouse_select_vector)){     //play choose cards ,only once each time
				Single_Card* ptr = nullptr;
					ptr= Human.cards.Search_Card_Position_locate(mouse_select_vector);
				if (ptr->mouse_select_card==false&&Human.select_card==false) {
					ptr->mouse_select_card = true;
					Human.select_card = true;
					button_ok.enable_diabled_button();
					button_cancel.enable_normal_button();
					button_discard.enable_diabled_button();
				}
				else if(ptr->mouse_select_card == true && Human.select_card == true){
					ptr->mouse_select_card = false;
					Human.select_card = false;
					Machine.being_choose = false;
				}
				return;   // once select one card, return to draw  ?that is needed?
			}
			
			if (Human.select_card){
				// find node that is chose
				Single_Card* ptr = Human.cards.Pile_Card_Total->next;
				for (int i = 0; i < Human.cards.Pile_Card_Amount; i++) {
					if (ptr->mouse_select_card) break;
					ptr = ptr->next;
				}
				if (ptr!=NULL&&ptr->card_info.can_attck) {    // if the select card then choose enemy  (window_width - 143) / 2, 40 // 宽 143 || 高 195
				    if (mouse_select_vector.x> (window_width - 143) / 2&&mouse_select_vector.x< (window_width - 143) / 2+143&&mouse_select_vector.y>40&&mouse_select_vector.y<195+40&&Machine.being_choose==false) {
						Machine.being_choose = true;
						button_ok.enable_normal_button();
						button_cancel.enable_diabled_button();
						button_discard.enable_diabled_button();
					}
					else if (mouse_select_vector.x > (window_width - 143) / 2 && mouse_select_vector.x < (window_width - 143) / 2 + 143 && mouse_select_vector.y>40 && mouse_select_vector.y < 195 + 40 && Machine.being_choose==true) {
						Machine.being_choose = false;
						button_ok.enable_diabled_button();
						button_cancel.enable_normal_button();
						button_discard.enable_diabled_button();
					}
					//else if(mouse_select_vector.x>)
				}
				return;
			}
// 			if ()
// 			{
// 			}


		}
	}
	void Machine_Round() {}

	void Draw() {

		Draw_Stable_Background();
		Draw_HumanPlayer();
		Draw_Machine();
		window.display();
	}
	void Draw_HumanPlayer() {
		Single_Card* ptr = Human.cards.Pile_Card_Total->next;
		for (int i=0;i<Human.cards.Pile_Card_Amount;i++){  // each card:  width 93 || height 130
			if (ptr->mouse_select_card) { 
				ptr->point_one.x = 165 + i * 93;
				ptr->point_one.y = window_height - 170;
				ptr->point_two.x = 165 + (i + 1) * 93;
				ptr->point_two.y = window_height - 170 + 130;
				ptr->sprite_card.setPosition(ptr->point_one.x, ptr->point_one.y);
			}
			else {
				ptr->point_one.x = 165 + i * 93;
				ptr->point_one.y = window_height - 135;
				ptr->point_two.x = 165 + (i + 1) * 93;
				ptr->point_two.y = window_height - 135 + 130;
				ptr->sprite_card.setPosition(ptr->point_one.x, ptr->point_one.y);
			}
			window.draw(ptr->sprite_card);
			ptr = ptr->next;
		} 
		//--->> judge which kind of state of button
		if (button_cancel.is_disabled) {
			button_cancel.sprite_disabled.setPosition(807, 694);
			window.draw(button_cancel.sprite_disabled);
		}
		else if (button_cancel.is_hover) {
			button_cancel.sprite_hover.setPosition(807, 694);
			window.draw(button_cancel.sprite_hover);
		}
		else if (button_cancel.is_down) {
			button_cancel.sprite_down.setPosition(807, 694);
			window.draw(button_cancel.sprite_down);
		}
		else if (button_cancel.is_normal) {
			button_cancel.sprite_normal.setPosition(807, 694);
			window.draw(button_cancel.sprite_normal);
		}
		if (button_discard.is_disabled) {
			button_discard.sprite_disabled.setPosition(874, 644);
			window.draw(button_discard.sprite_disabled);
		}
		else if (button_discard.is_hover) {
			button_discard.sprite_hover.setPosition(874, 644);
			window.draw(button_discard.sprite_hover);
		}
		else if (button_discard.is_down) {
			button_discard.sprite_down.setPosition(874, 644);
			window.draw(button_discard.sprite_down);
		}
		else if (button_discard.is_normal) {
			button_discard.sprite_normal.setPosition(874, 644);
			window.draw(button_discard.sprite_normal);
		}
		if (button_ok.is_disabled){
			button_ok.sprite_disabled.setPosition(807, 604);
			window.draw(button_ok.sprite_disabled);
		}
		else if (button_ok.is_hover){
			button_ok.sprite_hover.setPosition(807, 604);
			window.draw(button_ok.sprite_hover);
		}
		else if (button_ok.is_down) {
			button_ok.sprite_down.setPosition(807, 604);
			window.draw(button_ok.sprite_down);
		}
		else if (button_ok.is_normal) {
			button_ok.sprite_normal.setPosition(807, 604);
			window.draw(button_ok.sprite_normal);
		}

	}
	void Draw_Machine() {
		if (Machine.being_choose){
			sprite_being_chosen.setPosition((window_width - 143) / 2, 40);  // 宽 1140 || 高 600
			window.draw(sprite_being_chosen);
		}
	}
	void Draw_Stable_Background() {
		// draw background
		sprite_background.setPosition(0, 0);  // 宽 1140 || 高 600
		window.draw(sprite_background);
		// draw player equipment board
		sprite_player_equip_board.setPosition(0, window_height - 170);//宽 164 || 高 170
		window.draw(sprite_player_equip_board);
		// draw player hand-cards board
		sprite_player_hand_board.setPosition(164, window_height - 170);//宽 764 || 高 170
		window.draw(sprite_player_hand_board);
		// draw player button background
		sprite_player_button_background.setPosition(804, window_height - 168);//宽 106 || 高 168
		window.draw(sprite_player_button_background);
		// draw player general & role board
		sprite_player_role_background.setPosition(910, window_height - 170); // 宽 125 || 高 170
		window.draw(sprite_player_role_background);
		// draw npc board
		sprite_npcboard.setPosition((window_width - 143) / 2, 40); // 宽 143 || 高 195
		window.draw(sprite_npcboard);
		// draw npc cards board
		sprite_npc_cards.setPosition((window_width - 143) / 2, 103); // 宽 143 || 高 195
		window.draw(sprite_npc_cards);
		// draw piles & cards background
		sprite_piles_back.setPosition(window_width / 3, 300); // 宽 93 || 高 130
		window.draw(sprite_piles_back);
	}
	Game() {
		window_width = 1035;
		window_height = 770;
		window.create(sf::VideoMode(window_width, window_height), L"三国杀_BY_赵茜茜");
	}
};
