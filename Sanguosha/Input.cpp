#include "Game.h"

Vector2i Game::Input() {
	//Event event_global;
	while (window.pollEvent(event_global)) {
		if (event_global.type == Event::Closed) {
			window.close();
			gamequit = true;
		}
		//if (Human.round_play_phase||1){
		if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
			mouse_count_clock_two = Mouse::getPosition(window);
			if (mouse_click_timer.getElapsedTime().asMilliseconds() < 500 && mouse_count_clock_two.x - mouse_count_clock_one.x < 10 && mouse_count_clock_two.y - mouse_count_clock_one.y < 10) {
				cout << "Mouse::Left double click" << endl;
				cout << mouse_count_clock_two.x << " || " << mouse_count_clock_two.y << endl;
				return mouse_count_clock_two;
			}
			else if (mouse_count_clock_two.x > 807 && mouse_count_clock_two.x < (807 + 61) && mouse_count_clock_two.y > 604 && mouse_count_clock_two.y < (604 + 75) && !button_ok.is_disabled)
			{ // the button of ok //(807, 604)++(61,75)
				button_ok.enable_down_button();
				cout << "鼠标按下确定" << endl;
			}
			else if (mouse_count_clock_two.x > 807 && mouse_count_clock_two.x < (807 + 61) && mouse_count_clock_two.y > 694 && mouse_count_clock_two.y < (694 + 73) && !button_cancel.is_disabled)
			{ // the button of cancel //(807, 604)++(61,75)  
				button_cancel.enable_down_button();
				cout << "鼠标按下取消" << endl;
			}
			else if (mouse_count_clock_two.x > 874 && mouse_count_clock_two.x < (874 + 33) && mouse_count_clock_two.y > 644 && mouse_count_clock_two.y < (644 + 81) && !button_discard.is_disabled)
			{ // the button of discard //(807, 604)++(61,75)  
				button_discard.enable_down_button();
				cout << "鼠标按下结束" << endl;
			}

		}
		if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
			mouse_count_clock_one = Mouse::getPosition(window);
			//bool card_selected = Human.cards.Search_Card_Position(mouse_count_clock_one);
			mouse_click_timer.restart();
			//if (button_ok.is_down) button_ok.enable_normal_button();
			//if (button_cancel.is_down) button_cancel.enable_normal_button();
			//if (button_discard.is_down) button_discard.enable_normal_button();
			return mouse_count_clock_one;
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
					//cout << "鼠标位于取消上" << endl;
				}
				else {
					cout << "new mouse x: " << event_global.mouseMove.x << endl;
					cout << "new mouse y: " << event_global.mouseMove.y << endl;
					button_cancel.enable_normal_button();
					//cout << "鼠标不在取消上" << endl;
				}
			}
			// control button of assure
			if (!button_ok.is_disabled) {
				if (event_global.mouseMove.x > 807 && event_global.mouseMove.x < (807 + 61) && event_global.mouseMove.y > 604 && event_global.mouseMove.y < (604 + 75))
				{ // the button of ok //(807, 604)++(61,75)
					cout << "new mouse x: " << event_global.mouseMove.x << endl;
					cout << "new mouse y: " << event_global.mouseMove.y << endl;
					button_ok.enable_hover_button();
					//cout << "鼠标位于确定上" << endl;
					//return virtual_vector;
				}
				else {
					cout << "new mouse x: " << event_global.mouseMove.x << endl;
					cout << "new mouse y: " << event_global.mouseMove.y << endl;
					button_ok.enable_normal_button();
					//cout << "鼠标不在确定上" << endl;
				}
			}
			// control button of discard in hover state
			if (!button_discard.is_disabled) {
				if (event_global.mouseMove.x > 874 && event_global.mouseMove.x < (874 + 33) && event_global.mouseMove.y > 644 && event_global.mouseMove.y < (644 + 81))
				{ // the button of ok //(874, 644)++(33,81)
					cout << "new mouse x: " << event_global.mouseMove.x << endl;
					cout << "new mouse y: " << event_global.mouseMove.y << endl;
					button_discard.enable_hover_button();
					//cout << "鼠标位于结束上" << endl;
				}
				else {
					cout << "new mouse x: " << event_global.mouseMove.x << endl;
					cout << "new mouse y: " << event_global.mouseMove.y << endl;
					button_discard.enable_normal_button();
					//cout << "鼠标不在结束上" << endl;
				}
			}
		}
	}
}
