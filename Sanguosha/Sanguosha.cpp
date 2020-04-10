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
	//初始化

	Game Sanguosha;
    Skill card_skill;

 	while (Sanguosha.window.isOpen()){
 		do {
 			Sanguosha.Initial();
 			while (Sanguosha.window.isOpen() && Sanguosha.gameover == false) {
 				//Sanguosha.Input();
 				if (Sanguosha.new_round) Sanguosha.Round_Initialize(Sanguosha.turn);     // where exist new round ,there a turn to judge & initialize player's data
 				//Sanguosha.Input();
 				Sanguosha.Human_Round();
 				Sanguosha.Draw();
 			}
 		} while (!Sanguosha.gamequit);
 	}

			cout << "yes" << endl;
            //cout << "test!" << endl;
	//cout << temp << endl;
	return 0;
}
/*********************************************************************************************************

>>>>>>>>>2020.4.7 开发思路
思考：就是 引入 按钮 确定 取消 结束   ——和 设置 目标要关联起来o    以便以后 国战  单机多人 
思考：技能怎么引入是个大问题  加个技能类》》又不能引入别的参数   不知道加players 的类行不行  已知 game 类不行

>>>>>>>>>2020.4.8 开发思路
已解决：新增按钮类，按钮已经实现了基础框架——不同情况下可用or变黑，悬浮加亮
已解决：回合期间 击中牌可锁定目标了，并且在》类player下新增判断变量 bool select_card 判断当前是否选择卡牌来呈现 选择&非选择动画
已解决：锁定目标结合了 card_info下的 bool can_attack变量判断，这个在 pile_card 类中使用 bool card_can_attack(int number) 实现转变
待实现：合理应用input ,每次执行只返回 vector 所有操作在 logic 中 也就是huanm_round,目前局限为仅能使用一次input，此后尝试将 input 置于 游戏逻辑外 将 human_round & machine_round 结合为logic
待实现：按钮实现点击特效并且 打出牌 更新游戏状态
待实现：重大难题——攻克游戏技能施展？在哪施展？目前已知 skill 可以引入player类！放入game类？ 下次code的着重点—— huamn_round 杀后，machine 闪 实现！

**********************************************************************************************************/