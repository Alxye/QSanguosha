#include "Game.h"

/*************************************T  E  X  T__C  O  D  E***************/

// RenderWindow window;
// Vector2i p1, p2;
// Clock mouse_click_timer;
// 
// bool input() {
// 	sf::Event event;
// 	while (window.pollEvent(event))
// 	{
// 		if (event.type == sf::Event::Closed) {
// 			window.close();
// 			//gamequit = true;
// 		}
// 		if (event.type == sf::Event::EventType::KeyReleased && event.key.code == sf::Keyboard::Escape) {
// 			window.close();
// 			//gamequit = true;
// 		}
// 		//if mouse_click_timer(event.type==sf::Event::MouseButtonPressed&&event.mouseButton.button==sf::Mouse::Left){
// 		//	if (mouse_click_timer.getElapsedTime().asMilliseconds() > 500)	cout << "Mouse::Left Press" << endl;
// 		//	else cout << "Mouse::Left Double Clicked" << endl;
// 		//}
// 		//if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
// 		//	mouse_click_timer.restart();
// 		//	cout << "Mouse::Left Released" << endl;
// 		//}
// 		//if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right) {
// 		//	cout << "Mouse::Right Press" << endl;
// 		//}
// 
// 		if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
// 			p2 = Mouse::getPosition(window);
// 			if (mouse_click_timer.getElapsedTime().asMilliseconds() < 500 && p2.x - p1.x < 10 && p2.y - p1.y < 10)
// 			{
// 				cout << "Mouse::Left double click" << endl;
// 				return true;
// 			}
// 			else {
// 				cout<<"++++1" << endl;
// 				cout << "Mouse::Left click" << endl;
// 			}
// 		}
// 		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
// 			p1 = Mouse::getPosition(window);
// 			mouse_click_timer.restart();
// 			cout << "Mouse::Left Release" << endl;
// 		}
// 		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Right) {
// 			cout << "Mouse::Right Release" << endl;
// 			return true;
// 		}
// 	}
// }
// bool input_copy() {
// 	sf::Event event;
// 	while (window.pollEvent(event))
// 	{
// 		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Right) {
// 			cout << "Mouse::Right Release" << endl;
// 			return true;
// 		}
// 	}
// }
// void testfunc() {
// 	if (input_copy()) {
// 		cout << "?????" << endl;
// 	}
// }

/*************************************T  E  X  T__C  O  D  E***************/
int main() {

    cout << "666" << endl;
    //³õÊ¼»¯
	
    Game Sanguosha;

      while (Sanguosha.window.isOpen()) {
          do {
              Sanguosha.Initial();
              while (Sanguosha.window.isOpen() && Sanguosha.gameover == false) {
                  //Sanguosha.Input();
                  if (Sanguosha.new_round) Sanguosha.Round_Initialize(Sanguosha.turn);     // where exist new round ,there a turn to judge & initialize player's data
                  //if (Sanguosha.turn == 0) cout << "machine round" << endl;
                  //if (Sanguosha.turn == 1) cout << "human round" << endl;
                  if (!Sanguosha.animator_running) {
					  Sanguosha.Human_Round();
					  Sanguosha.Machine_Round();
                  }
                  Sanguosha.Draw();
              }
          } while (!Sanguosha.gamequit);
      }
    cout << "yes" << endl;
    return 0;
}
