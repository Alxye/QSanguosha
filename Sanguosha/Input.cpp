#include "Game.h"

void Game::Input_Globe() {
	cout << "so>?" << endl;
}

Vector2i Game::Input() {
	//Event event_global;
	while (window.pollEvent(event_global)) {
		// globe quit for console game
		if (event_global.type == Event::Closed) {
			window.close();
			gamequit = true;
		}

		// when game begin yet is showing the main menu
		if (gamestart) {
			// change style
			if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::A) {
				change_bg = true;
				if (globe_style_mode == 0) globe_style_mode = 1;
				else if (globe_style_mode == 1) globe_style_mode = 0;
			}
			if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
				//Mouse::getPosition(window) = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 570 && Mouse::getPosition(window).x < (570 + 80) && Mouse::getPosition(window).y > 50 && Mouse::getPosition(window).y < (50 + 400)){ 
					gamestart_go.enable_down_button();
				}
				else if (Mouse::getPosition(window).x > 470 && Mouse::getPosition(window).x < (470+ 80) && Mouse::getPosition(window).y > 90 && Mouse::getPosition(window).y < (90 + 400)){
					gamestart_info.enable_down_button();
				}
				else if (Mouse::getPosition(window).x > 370 && Mouse::getPosition(window).x < (370 + 80) && Mouse::getPosition(window).y > 130 && Mouse::getPosition(window).y < (130 + 400))	{
					gamestart_quit.enable_down_button();
				}
			}
			if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
				Mouse::getPosition(window) = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 570 && Mouse::getPosition(window).x < (570 + 80) && Mouse::getPosition(window).y > 50 && Mouse::getPosition(window).y < (50 + 400)) {
					gamestart_go.enable_diabled_button();
				}
				else if (Mouse::getPosition(window).x > 470 && Mouse::getPosition(window).x < (470 + 80) && Mouse::getPosition(window).y > 90 && Mouse::getPosition(window).y < (90 + 400)) {
					gamestart_info.enable_diabled_button();
				}
				else if (Mouse::getPosition(window).x > 370 && Mouse::getPosition(window).x < (370 + 80) && Mouse::getPosition(window).y > 130 && Mouse::getPosition(window).y < (130 + 400)) {
					gamestart_quit.enable_diabled_button();
				}
			}
			if (!gamestart_go.is_down && !gamestart_info.is_down && !gamestart_quit.is_down) {

				if (event_global.type == sf::Event::MouseMoved)
				{
					// control button of cancel in hover state
					if (event_global.mouseMove.x > 570 && event_global.mouseMove.x < (570 + 80) && event_global.mouseMove.y > 50 && event_global.mouseMove.y < (50 + 400))
					{
						if (gamestart_go.is_normal) button_animate_count = 0;
						gamestart_go.enable_hover_button();
					}
					else {
						gamestart_go.enable_normal_button();
					}
					// control button of assure
					if (event_global.mouseMove.x > 470 && event_global.mouseMove.x < (470 + 80) && event_global.mouseMove.y > 90 && event_global.mouseMove.y < (90 + 400))
					{
						if (gamestart_info.is_normal) button_animate_count = 0;
						gamestart_info.enable_hover_button();
					}
					else {
						gamestart_info.enable_normal_button();
					}
					// control button of discard in hover state
					if (event_global.mouseMove.x > 370 && event_global.mouseMove.x < (370 + 80) && event_global.mouseMove.y > 130 && event_global.mouseMove.y < (130 + 400))
					{
						if (gamestart_quit.is_normal) button_animate_count = 0;
						gamestart_quit.enable_hover_button();
					}
					else {
						gamestart_quit.enable_normal_button();
					}
				}
			}

		}
		// when begin to choose start game , choose game mode for double player or more
		if (gamechoose) {
			// change style
			if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::A) {
				change_bg = true;
				if (globe_style_mode == 0) globe_style_mode = 1;
				else if (globe_style_mode == 1) globe_style_mode = 0;
			}
			if (event_global.type == sf::Event::MouseMoved) {
				if (!button_gamechoose.is_down) {

					// control button of return-menu in hover state
					if (event_global.mouseMove.x > 430 &&
						event_global.mouseMove.x < (430 + 135) &&
						event_global.mouseMove.y > 174 &&
						event_global.mouseMove.y < (174 + 53)) {
						button_gamechoose.enable_hover_button();
						button_gamechoose.sprite_hover.setPosition(383, 188);
					}
					else if (event_global.mouseMove.x > 430 &&
						event_global.mouseMove.x < (430 + 135) &&
						event_global.mouseMove.y > 250 &&
						event_global.mouseMove.y < (250 + 53)) {
						button_gamechoose.enable_hover_button();
						button_gamechoose.sprite_hover.setPosition(383, 266);
					}
					else if (event_global.mouseMove.x > 430 &&
						event_global.mouseMove.x < (430 + 135) &&
						event_global.mouseMove.y > 330 &&
						event_global.mouseMove.y < (330 + 53)) {
						button_gamechoose.enable_hover_button();
						button_gamechoose.sprite_hover.setPosition(383, 344);
					}
					else if (event_global.mouseMove.x > 430 &&
						event_global.mouseMove.x < (430 + 135) &&
						event_global.mouseMove.y > 410 &&
						event_global.mouseMove.y < (420 + 53)) {
						button_gamechoose.enable_hover_button();
						button_gamechoose.sprite_hover.setPosition(383, 422);
					}
					else {
						button_gamechoose.enable_normal_button();
					}
				}
				// control button of return-menu in hover state
				if (return_button.is_normal || return_button.is_hover) {
					if (event_global.mouseMove.x > 890 && event_global.mouseMove.x < (890 + 100) && event_global.mouseMove.y > 640 && event_global.mouseMove.y < (640 + 90)) {
						return_button.enable_hover_button();
					}
					else {
						return_button.enable_normal_button();
					}
				}
			}
			
			if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
				//mouse_count_clock_two = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 890 && 
					Mouse::getPosition(window).x < (890 + 100) && 
					Mouse::getPosition(window).y > 640 && 
					Mouse::getPosition(window).y < (640 + 90)) {
					return_button.enable_down_button();
				}
				else if ( Mouse::getPosition(window).x > 430 &&
					 Mouse::getPosition(window).x < (430 + 135) &&
					 Mouse::getPosition(window).y > 174 &&
					 Mouse::getPosition(window).y < (174 + 53)) {
					button_gamechoose.enable_down_button();
					machine_number = 1;
				}
				else if ( Mouse::getPosition(window).x > 430 &&
					 Mouse::getPosition(window).x < (430 + 135) &&
					 Mouse::getPosition(window).y > 250 &&
					 Mouse::getPosition(window).y < (250 + 53)) {
					button_gamechoose.enable_down_button();
					machine_number = 2;
				}
				else if ( Mouse::getPosition(window).x > 430 &&
					 Mouse::getPosition(window).x < (430 + 135) &&
					 Mouse::getPosition(window).y > 330 &&
					 Mouse::getPosition(window).y < (330 + 53)) {
					button_gamechoose.enable_down_button();
					machine_number = 3;
				}
				else if ( Mouse::getPosition(window).x > 430 &&
					 Mouse::getPosition(window).x < (430 + 135) &&
					 Mouse::getPosition(window).y > 410 &&
					 Mouse::getPosition(window).y < (420 + 53)) {
					button_gamechoose.enable_down_button();
					machine_number = 4;
				}
			}
			if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
				//mouse_count_clock_two = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 890 && Mouse::getPosition(window).x < (890 + 100) && Mouse::getPosition(window).y > 640 && Mouse::getPosition(window).y < (640 + 90)) {
					return_button.enable_diabled_button();
				}
			}
		
		}
		// when gameinfo
		if (gameinfo) {
			// change style
			if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::A) {
				change_bg = true;
				if (globe_style_mode == 0) globe_style_mode = 1;
				else if (globe_style_mode == 1) globe_style_mode = 0;
			}
			if (event_global.type == sf::Event::MouseMoved) {
				// control button of return-menu in hover state
				if (return_button.is_normal || return_button.is_hover) {
					if (event_global.mouseMove.x > 890 && event_global.mouseMove.x < (890 + 100) && event_global.mouseMove.y > 640 && event_global.mouseMove.y < (640 + 90)) {
						return_button.enable_hover_button();
					}
					else {
						return_button.enable_normal_button();
					}
				}
				
				// control thanks button
				if (!gameinfo_thanks.is_down) {
					if (event_global.mouseMove.x > 459 && event_global.mouseMove.x < (459 + 80) && event_global.mouseMove.y > 445 && event_global.mouseMove.y < (445 + 136)) {
						if (gameinfo_thanks.is_normal) button_animate_count = 0;
						gameinfo_thanks.enable_hover_button();
					}
					else {
						gameinfo_thanks.enable_normal_button();
					}
				}
				// control gameinfo button
				if (!gameinfo_gameinfo.is_down) {
					if (event_global.mouseMove.x > 529 && event_global.mouseMove.x < (529 + 86) && event_global.mouseMove.y > 430 && event_global.mouseMove.y < (430 + 183)) {
						if (gameinfo_gameinfo.is_normal) button_animate_count = 0;
						gameinfo_gameinfo.enable_hover_button();
					}
					else {
						gameinfo_gameinfo.enable_normal_button();
					}
				}
				// control phaseinfo button
				if (!gameinfo_phaseinfo.is_down) {
					if (event_global.mouseMove.x > 603 && event_global.mouseMove.x < (603 + 86) && event_global.mouseMove.y > 430 && event_global.mouseMove.y < (430 + 183)) {
						if (gameinfo_phaseinfo.is_normal) button_animate_count = 0;
						gameinfo_phaseinfo.enable_hover_button();
					}
					else {
						gameinfo_phaseinfo.enable_normal_button();
					}
				}
				// control cardinfo button
				if (!gameinfo_cardinfo.is_down) {
					if (event_global.mouseMove.x > 673 && event_global.mouseMove.x < (673 + 86) && event_global.mouseMove.y > 430 && event_global.mouseMove.y < (430 + 183)) {
						if (gameinfo_cardinfo.is_normal) button_animate_count = 0;
						gameinfo_cardinfo.enable_hover_button();
					}
					else {
						gameinfo_cardinfo.enable_normal_button();
					}
				}
			}


			if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
				//mouse_count_clock_two = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 890 && Mouse::getPosition(window).x < (890 + 100) && Mouse::getPosition(window).y > 640 && Mouse::getPosition(window).y < (640 + 90)) {
					return_button.enable_down_button();
				}
				// control thanks button
				else if (Mouse::getPosition(window).x > 459 && Mouse::getPosition(window).x < (459 + 80) && Mouse::getPosition(window).y > 445 && Mouse::getPosition(window).y < (445 + 136)) {
					gameinfo_thanks.enable_down_button();
					gameinfo_gameinfo.enable_normal_button();
					gameinfo_phaseinfo.enable_normal_button();
					gameinfo_cardinfo.enable_normal_button();

				}
				// control gameinfo button
				else if (Mouse::getPosition(window).x > 529 && Mouse::getPosition(window).x < (529 + 86) && Mouse::getPosition(window).y > 430 && Mouse::getPosition(window).y < (430 + 183)) {
					gameinfo_gameinfo.enable_down_button();
					gameinfo_phaseinfo.enable_normal_button();
					gameinfo_cardinfo.enable_normal_button();
					gameinfo_thanks.enable_normal_button();
				}
				// control phaseinfo button
				else if (Mouse::getPosition(window).x > 603 && Mouse::getPosition(window).x < (603 + 86) && Mouse::getPosition(window).y > 430 && Mouse::getPosition(window).y < (430 + 183)) {
					gameinfo_phaseinfo.enable_down_button();
					gameinfo_cardinfo.enable_normal_button();
					gameinfo_thanks.enable_normal_button();
					gameinfo_gameinfo.enable_normal_button();
				}
				// control cardinfo button
				else if (Mouse::getPosition(window).x > 673 && Mouse::getPosition(window).x < (673 + 86) && Mouse::getPosition(window).y > 430 && Mouse::getPosition(window).y < (430 + 183)) {
					gameinfo_cardinfo.enable_down_button();
					gameinfo_thanks.enable_normal_button();
					gameinfo_gameinfo.enable_normal_button();
					gameinfo_phaseinfo.enable_normal_button();
				}
			}
			if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
				mouse_count_clock_two = Mouse::getPosition(window);
				if (Mouse::getPosition(window).x > 890 && Mouse::getPosition(window).x < (890 + 100) && Mouse::getPosition(window).y > 640 && Mouse::getPosition(window).y < (640 + 90)) {
					return_button.enable_diabled_button();
				}
			}

		}
		// when game pause --only when game is running can it be enabled
		if (gamepause) {

		}
        // human operate of gameover
		if (gameover) {

		}

		if (gamerun) {
			// change image
			if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::A) {
				if (img_bg_number == 4) img_bg_number = 0;
				else img_bg_number++;
				change_bg = true;
			}
			if (event_global.type == sf::Event::EventType::KeyReleased && event_global.key.code == sf::Keyboard::Q) {
				restart = true;
			}

			if (event_global.type == Event::MouseButtonPressed && event_global.mouseButton.button == Mouse::Left) {
				mouse_count_clock_two = Mouse::getPosition(window);
				if (mouse_count_clock_two.x > 807 && mouse_count_clock_two.x < (807 + 61) && mouse_count_clock_two.y > 604 && mouse_count_clock_two.y < (604 + 75) && !button_ok.is_disabled)
				{ // the button of ok //(807, 604)++(61,75)
					button_ok.enable_down_button();
				}
				else if (mouse_count_clock_two.x > 807 && mouse_count_clock_two.x < (807 + 61) && mouse_count_clock_two.y > 694 && mouse_count_clock_two.y < (694 + 73) && !button_cancel.is_disabled)
				{ // the button of cancel //(807, 604)++(61,75)  
					button_cancel.enable_down_button();
				}
				else if (mouse_count_clock_two.x > 874 && mouse_count_clock_two.x < (874 + 33) && mouse_count_clock_two.y > 644 && mouse_count_clock_two.y < (644 + 81) && !button_discard.is_disabled)
				{ // the button of discard //(807, 604)++(61,75)  
					button_discard.enable_down_button();
				}
			}
			if (event_global.type == Event::MouseButtonReleased && event_global.mouseButton.button == Mouse::Left) {
				mouse_count_clock_one = Mouse::getPosition(window);
				//bool card_selected = Human.cards.Search_Card_Position(mouse_count_clock_one);
				mouse_click_timer.restart();
				return mouse_count_clock_one;
			}

			if (event_global.type == sf::Event::MouseMoved)
			{
				// control button of cancel in hover state
				if (!button_cancel.is_disabled) {
					if (event_global.mouseMove.x > 807 && event_global.mouseMove.x < (807 + 61) && event_global.mouseMove.y > 694 && event_global.mouseMove.y < (694 + 73))
					{ // the button of cancel //(807, 694)++(61,73)
						//cout << "new mouse x: " << event_global.mouseMove.x << endl;
						//cout << "new mouse y: " << event_global.mouseMove.y << endl;
						button_cancel.enable_hover_button();
						//cout << "鼠标位于取消上" << endl;
					}
					else {
						//cout << "new mouse x: " << event_global.mouseMove.x << endl;
						//cout << "new mouse y: " << event_global.mouseMove.y << endl;
						button_cancel.enable_normal_button();
						//cout << "鼠标不在取消上" << endl;
					}
				}
				// control button of assure
				if (!button_ok.is_disabled) {
					if (event_global.mouseMove.x > 807 && event_global.mouseMove.x < (807 + 61) && event_global.mouseMove.y > 604 && event_global.mouseMove.y < (604 + 75))
					{ // the button of ok //(807, 604)++(61,75)
						//cout << "new mouse x: " << event_global.mouseMove.x << endl;
						//cout << "new mouse y: " << event_global.mouseMove.y << endl;
						button_ok.enable_hover_button();
						//cout << "鼠标位于确定上" << endl;
						//return virtual_vector;
					}
					else {
						//cout << "new mouse x: " << event_global.mouseMove.x << endl;
						//cout << "new mouse y: " << event_global.mouseMove.y << endl;
						button_ok.enable_normal_button();
						//cout << "鼠标不在确定上" << endl;
					}
				}
				// control button of discard in hover state
				if (!button_discard.is_disabled) {
					if (event_global.mouseMove.x > 874 && event_global.mouseMove.x < (874 + 33) && event_global.mouseMove.y > 644 && event_global.mouseMove.y < (644 + 81))
					{ // the button of ok //(874, 644)++(33,81)
						//cout << "new mouse x: " << event_global.mouseMove.x << endl;
						//cout << "new mouse y: " << event_global.mouseMove.y << endl;
						button_discard.enable_hover_button();
						//cout << "鼠标位于结束上" << endl;
					}
					else {
						//cout << "new mouse x: " << event_global.mouseMove.x << endl;
						//cout << "new mouse y: " << event_global.mouseMove.y << endl;
						button_discard.enable_normal_button();
						//cout << "鼠标不在结束上" << endl;
					}
				}
			    
			}
			
		}
	}
	return virtual_vector;
}
