# Sanguosha
support by SFML &amp; C++  
## 2020.4.7 开发思路  
* 思考：就是 引入 按钮 确定 取消 结束 和 设置 目标要关联起来   以便以后 国战  单机多人   
* 思考：技能怎么引入是个大问题  加个技能类》》又不能引入别的参数   不知道加players 的类行不行  已知 game 类不行  
## 2020.4.8 开发思路  
*已解决：新增按钮类，按钮已经实现了基础框架——不同情况下可用or变黑，悬浮加亮  
已解决：回合期间 击中牌可锁定目标了，并且在》类player下新增判断变量 bool select_card 判断当前是否选择卡牌来呈现 选择&非选择动画  
已解决：锁定目标结合了 card_info下的 bool can_attack变量判断，这个在 pile_card 类中使用 bool card_can_attack(int number) 实现转变*   
* 待实现：合理应用input ,每次执行只返回 vector 所有操作在 logic 中 也就是huanm_round,目前局限为仅能使用一次input，此后尝试将 input 置于 游戏逻辑外 将 human_round & machine_round 结合为logic  
* 待实现：按钮实现点击特效并且 打出牌 更新游戏状态   
* 待实现：重大难题——攻克游戏技能施展？在哪施展？目前已知 skill 可以引入player类！放入game类？ 下次code的着重点—— huamn_round 杀后，machine 闪 实现！
## 2020.4.10 开发思路 
*已解决：已实现出牌阶段按钮的动画，包括 悬浮，按下，复原，不可用 状态，调试尚无明显bug   
已解决：游戏回合逻辑初步实现，引入 Skill 类下技能判断的bool变量，该 Skill 类依赖于 Player 类以及游戏回合逻辑，并且在出牌期间，来回转换。   
已解决：游戏出牌动画，杀、闪、桃、酒、受伤动画，绑定 Player 类并进行实现   
已解决：完善游戏画面的绘制，绘制玩家血量&npc血量，后期可以根据阵营，绘制不同颜色的血量*
* 待实现：游戏出牌阶段结束后，进入弃牌阶段，保证同时丢弃多张牌，并有按钮动画，以及游戏提示界面（绘制模块）
* 待实现：游戏出牌阶段，有些牌是被动或者是受约束的，比如闪、只能出一次的杀，比如无懈可击。下次coding该引入enable变量判断，整顿input模块，引入卡牌变灰，不可点击的情况（Human_round)     
* 警示！注意一定要保证 input 模块的完整独立性，就是输出用户交互的坐标
## 2020.4.11 开发思路
*已解决：在card中引入 enable bool 变量，实现对卡牌可选择&可不选择的控制判断，不可选择则变灰    
已解决：初步将弃牌阶段独立于出牌阶段，弃牌阶段的input模块已独立于出牌阶段    
已解决：在绘制模块新增子模块——draw_human_player & draw_machine_player & draw_animator; 相应子模块有相应绘制函数。*    
* 待实现：完善 弃牌阶段 logic & input   
* 待实现：开发游戏AI   
* 思考：目标完善后，该走 完善卡牌武将阵营  还是  新增游戏玩家
## 2020.4.17 开发思路
*已解决：将input函数完全独立于逻辑模块（重大成功）！使得input函数仅用来做人类玩家交互动作，以鼠标位置为返回值传值，达到分离把控，一次逻辑，一次绘图，一次交互！   
已解决：card 类中enable_to_play已完美融入游戏逻辑，通过该类bool变量来判断卡牌是否可被人为点击，增强了游戏的交互性，同时，将卡牌选择的bug降低了，对玩家来讲，能更直观地选择卡牌、打牌、弃牌！   
已解决：已完善游戏回合！能实现杀、闪、桃游戏循环，游戏框架已基本搭建完成，可通过skill类在游戏逻辑间判断，实现技能牌使用。   
已解决：弃牌阶段，多重选择卡牌，并且有上限地选择卡牌，并能实时绘制，同时加入按钮交互。  
已解决：在Game类中引入human_defense布尔变量，实现在机器回合中，玩家可以采取防御手段，并且实现交互，目前已载入“闪”的用户交互防御logic，并且能独立绘制动画。   
已解决：被动防御期间，仅能选择一张卡牌打出，玩家可以选择不打牌或者无牌可打。*
* 待实现：约束杀的次数。    
* 待实现：增加卡牌技能数。 
### 2020.4.18 开发思路
*已解决：杀的次数可被约束，作用于人类与机器——具体方法，player类引入int类型约束变量，游戏开始回合中通过新增判断实现enable_to_player的变更*
``` 
int kill_limit;             // the limit number that player use kill && normally is 1
int kill_times;             // the number that player use kill && normally is 0 when play one kill,it ++  
=====>>Human_Round // ptr is a pointer that directs to node of kill card 
if(Human.kill_times<Human.kill_limit) ptr->enable_to_play = true;
else  ptr->enable_to_play = false;
=====>>Machine_Round as same but pointer is not needed
```  
*已解决：修复了被动交互技能阶段，已选择card，点击cancel时，卡牌不能自动回归的bug    
已解决：完善了按钮动画按下特效，能体现按下特效，并且在松开时才继续执行。   
已解决：完善了杀、桃、酒、闪的技能逻辑循环，并且能在人类与machine间来回跳转，互相独立      
已解决：Game类新引入animator_running的bool变量，使得动画播放独立于游戏逻辑，并且动画期间，游戏logic不可用，达到减缓作用——machine技能释放减缓。*   
* 待修复查证：非常非常偶尔出现，出桃变成出闪，尚未发现问题？？？    
* 待实现：加入马和武器（近期目标）    
### 2020.4.23 开发思路
*已优化：将类函数结构调整，已initial、input、logic、draw为基本，使得后续代码编辑优化作便捷。*   
* 待实现：濒死状态 bug 修复！ 实现回合间跳转！  
### 2020.4.24 开发思路
*已解决：将回合结构重新调整，加入exturn&exturn_backup的int形变量，进行约束，新增eunm类型充当每个round可以出牌的对象，通过exturn实现回合之间的跳转。   
已解决：完善了濒死状态的回合跳转，新增了死亡判断，结合extra可以实现多人模式下，他人出桃救人的逻辑，具体思路如下：本回合出牌者，每出一次攻击类型的牌，然后exturn变更为受攻击者，比如machine，然后回合跳转至machine，开启被动防御，若防御失败若为濒死状态，则将对非濒死者发出begging_peach的信号，并且exturn为攻击者（后期将引入exturn_backup对应攻击者编号），当前exturn 对象选择出桃，则跳转求桃者，回血超过0，则濒死状态结束，exturn回归正常normal状态，继续由攻击者出牌模式；若当前exturn 对象不选择出桃，则跳转下一对象，直到轮到濒死者自救，濒死者若自救失败，死亡，自救成功，则游戏变成normal状态。*
* 待优化：先实现多人局，再引入濒死状态。
### 2020.4.28 开发思路
*已解决：初步引入Machine[]数组实现多人单机回合制*  
```
if(!Human.die && (exturn == normal||exturn==human)) Human_Round();
if (!Machine[0].die && (exturn == normal || exturn == machine_0)) Machine_Round(Machine[0]);
if (!Machine[1].die && (exturn == normal || exturn == machine_1)) Machine_Round(Machine[1]);
if (!Machine[2].die && (exturn == normal || exturn == machine_2)) Machine_Round(Machine[2]);
if (!Machine[3].die && (exturn == normal || exturn == machine_3)) Machine_Round(Machine[3]);
```
* 待优化：多人局的turn问题  
### 2020.5.3 开发思路
*已解决：开辟枚举变量，并且赋值于turn，使得更直观了，基本实现回合轮转* 
```
switch (turn){
	case human:          // humans round
		Human.round_draw_phase = true;
		Human.round_play_phase = true;
	    break;
	case machine_0:      // machine's round--->0		
		Machine[0].round_draw_phase = true;
		Machine[0].round_play_phase = true;
		break;
	case machine_1:      // machine's round--->1	
		Machine[1].round_draw_phase = true;
		Machine[1].round_play_phase = true;
		break;
	case machine_2:      // machine's round--->2		
		Machine[2].round_draw_phase = true;
		Machine[2].round_play_phase = true;
		break;
	case machine_3:      // machine's round--->3		
		Machine[3].round_draw_phase = true;
		Machine[3].round_play_phase = true;
		break;
	default:
		break;
	}
```
* 待优化：extra-turn被动回合的回合轮转问题
### 2020.5.12 开发思路
*已解决：更新了Player类，给每个player对象新增charactor_code的int型变量，用来表明对象身份，可以用于定位对象。  
已解决：Machine对象的player回合采用传递参数的方法进行执行，确保安全性，封装起来便于后期维护,此外，还可以在machine回合内对其他machine对象的值的搜寻，使得一般化游戏逻辑，为后续人数设置保留接口*
```
// machine round logic
void Machine_Round_Initialize(Player& machine);
int Machine_Round_Skill_Judgment(Player& machine);
void Machine_Round_enable_dying_state(Player& machine);
void Machine_Round(Player & machine);
```
*已解决：在Game类引入了peach-begger来标志目前濒死者（即发送求桃信号的玩家对象），便于后期给桃能正确地给到求桃对象。   
已解决：完善int型exta-turn-backup变量的应用情况，在濒死状态下，可用于保存当前出桃者回合，回合可中途调整至求桃者回合回血，并且再加以判断是否仍然处于濒死状态，同时，还可以实现出桃者出多个桃救求桃者，exta-turn-backup非应用场合下，其值为-1，以防未知错误，同时出现回合逻辑错误，也便于追踪。*
```
// >>>>>>>求桃者>>>>>>血量判定>>>>>回合跳转判定
if (machine.HP <= 0) {
	exturn = machine.charactor_code;
	machine.self_save = true;
	machine.is_dying = true;
	exturn = exturn_backup;// make player plays more peach to save player possible
	exturn_backup = -1;    // default exturn_backup value in case there got unknown error
}
else {
	exturn = normal;
	exturn_backup = -1;    // default exturn_backup value in case there got unknown error
	machine.self_save = false;
	machine.is_dying = false;
}
// >>>>>>>出桃者>>>>>>回合跳转判定
if (machine.cards.Search_Card(peach)) {
	// figure out who sent begging peach signal then give it
    ...
	...
	// go to peach-begger then having peach;also back up current state of turn for the situation that peach-begger is still in dying state even after get one blood recovered
	exturn_backup = exturn;
	exturn = peach_begger;
}
else {  // when machine don't mean to give peach ,ask next one
	// if there exist more machine then change it another machine to judge 
	if (exturn == machine_3) exturn = human;  // meaning going to a loop
	else exturn++;
}
```
*已解决：引入了bool型变量round-loop来辅助濒死阶段是否已完成一个回合，用于保证即使玩家不出桃就自己，后续有npc出桃也能救活，避免不公平性bug。
已解决：完善了濒死状态（尚未调试），可实现无论从哪一方开始进入濒死，死亡判断只在回合轮过一圈后才判定。结合int型round_loop_starter变量确定loop开始者，用以标记loop的尽头。     
已解决：完善多人单机的machine-logic模块*
* 待实现：完善多人单机的human-logic模块
### 2020.5.13 开发思路
*已解决：改进了多人状态下濒死的判断，并且解决了非濒死状态下，求桃的bug。   
已解决：完善了human-logic多人单机的函数，玩家模块引入了坐标对象，使得更方便的进行enemy定位*
```
Vector2i location_one;    // in order to locate machine's position--Upper left corner
Vector2i location_two;    // in order to locate machine's position--Lower right corner
```
* 待解决：实现draw模块的多人单机函数的纠正同化   
### 2020.5.14 开发思路
*已解决：将多人单机所有logic&drew函数修正完毕，并且能相对正常显示再程序当中。*
### 2020.5.16 开发思路
*已解决：round-轮转bug，回合问题bug。*
* 待实现：动画一个一个播放，加入文字内容提示，当前回合位，提示当前操作
### 2020.5.20 开发思路
*已解决：回合bug，使得真正回合轮转*
``` // 修正--Machine_Round_Initialize--下此下代码片段（附修正代码）
if (machine.HP > 0 /* 新增判断变量 && Human.is_dying */ ) {
	machine.is_dying = false;
	machine.die = false;
	machine.self_save = false;
	exturn = normal;
}
```
* 待实现：引入出牌阶段、弃牌阶段、摸牌阶段、判断阶段、濒死求桃阶段的界面提示框。
### 2020.5.21 开发思路
*已解决：初步引入出牌阶段、弃牌阶段、摸牌阶段、判断阶段、濒死求桃阶段的界面提示框*
``` 
//在core.h中 player类引入 texture&sprite成员
class Player{
...
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
...
}
// 在initial函数素材加载中初始化
//---->> Phase mask border for machine
for (int number = 0; number < 4; number++) {
	Load_Image(Machine[number].texture_draw_phase, Machine[number].sprite_draw_phase, "image/phase/draw.png", 0, 0, 1, 1);
	Load_Image(Machine[number].texture_play_phase, Machine[number].sprite_play_phase, "image/phase/play.png", 0, 0, 1, 1);
	Load_Image(Machine[number].texture_discard_phase, Machine[number].sprite_discard_phase, "image/phase/discard.png", 0, 0, 1, 1);
	Load_Image(Machine[number].texture_judge_phase, Machine[number].sprite_judge_phase, "image/phase/judge.png", 0, 0, 1, 1);
	Load_Image(Machine[number].texture_response_phase, Machine[number].sprite_response_phase, "image/phase/response.png", 0, 0, 1, 1);
	Load_Image(Machine[number].texture_sos_phase, Machine[number].sprite_sos_phase, "image/phase/sos.png", 0, 0, 1, 1);
}
```
*已解决：修复了交互时候，玩家不能正确杀machine的姿势，在logic-human中的exturn变更swich中附加break;(详情代码不附）*
*已解决：使动画逐一播放，拖延ai速度，防止混乱，解决方案：将!animator_running的判断条件附在每一个round-logic中*
* 待实现：引入出牌阶段、弃牌阶段、摸牌阶段、判断阶段、濒死求桃阶段的界面提示框。
### 2020.5.29 开发思路
*已解决：解决了，一到human濒死就死机且不循环的bug。苍天大地啊...bug居然是enable_state后面小小一行 exturn=normal;找问题数天....*
### 2020.6.3 开发思路
*已解决：更改游戏模式，变成无尽模式，引入killing_number计数玩家杀敌统计，并且显示,下附代码（更正版本），其中玩家死亡，则置标志位为true，该条件只在攻击者求桃轮转一圈且自救无效后才触发。*
```
// about begger-life
	if (Human.skill.begging_peach == false && round_loop && round_loop_starter == human) {
		switch (peach_begger)
		{
		case human:
			if (Human.HP <= 0) Human.die = true;
			break;
		case machine_0:
			if (Machine[0].HP <= 0) {
				//Machine[0].die = true;
				Machine[0].die = false;
				Machine[0].skill.begging_peach = false;
				Machine[0].self_save = false;
				Machine[0].HP = 4;
				Machine[0].limited_HP = 4;
				killing_number++;
			}
			break;
		case machine_1:
			if (Machine[1].HP <= 0) {
				//Machine[1].die = true;
				Machine[1].die = false;
				Machine[1].skill.begging_peach = false;
				Machine[1].self_save = false;
				Machine[1].HP = 4;
				Machine[1].limited_HP = 4;
				killing_number++;
			}
			break;
		case machine_2:
			if (Machine[2].HP <= 0) {
				//Machine[2].die = true;
				Machine[2].die = false;
				Machine[2].skill.begging_peach = false;
				Machine[2].self_save = false;
				Machine[2].HP = 4;
				Machine[2].limited_HP = 4;
				killing_number++;
			}
			break;
		case machine_3:
			if (Machine[3].HP <= 0) {
				//Machine[3].die = true;
				Machine[3].die = false;
				Machine[3].skill.begging_peach = false;
				Machine[3].self_save = false;
				Machine[3].HP = 4;
				Machine[3].limited_HP = 4;
				killing_number++;
			}
			break;
		default:
			break;
		}
		round_loop = false;
		round_loop_starter = -1; // default value is -1 to escape & found unknown error
		exturn = normal;
		exturn_backup = -1;
		return 0;
	}
```
*已实现：新增了自定义玩家局数，可双人局、三人局、四人局、五人局。*
```
// Game类新增machine_number用于计数当前局数
// Logic 模块新增 swich 对人数的逻辑判定
```
### 2020.6.6 开发思路
*已实现：解决窗口拉伸&最大化问题，禁用！*
*已实现：增加绘制machine卡牌数量。*
*已实现：修正machine无法正确弃牌的bug *

```
while (machine.cards.Pile_Card_Amount > machine.HP) {
	machine.cards.Delete_Card(machine.cards.Pile_Card_Total->next->card_info.single_card_number);
}
```
*已实现：修正了动画显示被遮挡的bug... *
*已实现：新增了弃牌堆的显示，前六张,引入texture&sprite反复绘制，通过start-draw来标记开始要绘制的张数*

```
void Game::Draw_Discard_Pile() {
	Single_Card* ptr = discard_pile.Pile_Card_Total->next;
	int start_draw = 1;
	if (discard_pile.Pile_Card_Amount - start_draw > 6) {
		Load_Image(texture_discard_pile, sprite_discard_pile, "image/back_stable/pile_back.png");
		sprite_discard_pile.setPosition(window_width / 2, 300);
		window.draw(sprite_discard_pile);
	}
	while (discard_pile.Pile_Card_Amount - start_draw > 6) {
		start_draw++;
		ptr = ptr->next;
	}
	int dx = 1;
	while (ptr) {
		switch (ptr->card_info.single_card_number)
		{
		case kill:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/0.jpg");
			break;
		case jink:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/1.jpg");
			break;
		case analeptic:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/2.jpg");
			break;
		case peach:
			Load_Image(texture_discard_pile, sprite_discard_pile, "image/skill&equip_card/small_card/3.jpg");
			break;
		default:
			break;
		}
		sprite_discard_pile.setPosition(window_width / 2 + dx * 20, 300);
		window.draw(sprite_discard_pile);
		dx++;
		ptr = ptr->next;
	}
}
```

*已实现：引入了Message_Box链表，来实现消息框的实时展现,新增信息插入&信息删除的Game成员函数*

```
typedef struct Message {  // message box
	wstring single_message;
	Message* next;
}Message, * Message_Box;
void Insert_Message(wstring str) {
	Message_Box S = new Message;
	S->next = NULL;
	S->single_message = str;
	Message_Box P = message;
	while (P->next)
		P = P->next;  // find tail node
	P->next = S;
	P = S;
	cout << "***********yes insert message succeed!!!" << endl;
	message_amount++;
}
void Delete_Message() {
	Message_Box T = message;
	while (T->next) {
		Message_Box p = T->next;
		T->next = p->next;
		delete p;
		message_amount--;
		cout << "<<<<message card succeed!!!" << endl;
		break;
	}
	return;
}
```

*已实现：同步绘制消息框，并加以约束，限定在15条。*

```
void Game::Draw_Text_Console() {
	RectangleShape rect(Vector2f(330,230)); // draw rectangle
	rect.setFillColor(Color(0, 0, 0, 100));
	rect.setPosition(700, 60);
	window.draw(rect);
	// when message amount is out of 15 ,then delete previous message in case the latest message is overflow
	while (message_amount > 15) {
		Delete_Message();
	}
	// show each message in message box
	Message_Box ptr = message->next;
	int dx = 0;
	while (ptr) {
		Font text_font;
		Text text;
		Load_Font(text_font, text, "font/simsun.ttc");
		text.setCharacterSize(15);
		text.setFillColor(Color(255, 255, 255, 255));
		text.setStyle(Text::Bold);
		text.setPosition(705, 60+dx*15);
		wstring each_line = L"";
		each_line = each_line + ptr->single_message;
		text.setString(each_line);
		window.draw(text);
		dx++;
		ptr = ptr->next;
	}
}
```
*已实现：完善了machine不同阶段的绘制,具体实现在draw模块，实现方法：在Player对象引入多组texture&sprite对应不同的阶段，在initial中初始化素材，在draw中根据machine对象的回合参数分别定位并确定绘制。*
*已实现：完成了所有消息的发送显示。遍布于logic函数中。主要思路：在每次的操作于状态位，都插入消息语句并显示。*
*已实现：完成了不同玩家局数，绘制不同面板。并且对高度进行了替代调整。*
*已实现：重大模块新增——游戏开始模块、游戏暂停模块、游戏退出模块、游戏结束统计模块、游戏关卡旋转模块、游戏说明与感谢模块。*
* 待实现：完善各个模块，且不要冲突。 
* 待实现：Input 全局与human局部会冲突卡顿的bug带解除。

### 2020.6.7 开发思路
*已实现：游戏开始模块。具体思路：|| 在Game类中引入3个Button类型对象||Initial函数中默认纹理素材||Draw函数中对不同情况下Button成员的值进行判定并绘制||借用animate-counter计数来实现擦除动画效果||Input模块中以鼠标交互对应按钮，通过启用Button成员函数，实现Button跨模块的同步||*

```
// 擦除动画实现 全局增设 int 型 button_animate_count 变量
if (button_animate_count < 81) {
	window.setFramerateLimit(200);
	if (gamestart_go.is_hover)	gamestart_go.sprite_hover.setTextureRect(IntRect(0, 0, 80, button_animate_count * 5));
	if (gamestart_info.is_hover)gamestart_info.sprite_hover.setTextureRect(IntRect(0, 0, 80, button_animate_count * 5));
	if (gamestart_quit.is_hover)gamestart_quit.sprite_hover.setTextureRect(IntRect(0, 0, 80, button_animate_count * 5));
	button_animate_count++;
	if (button_animate_count == 81)
		window.setFramerateLimit(300);
}
```
*已实现：解决了全局Input & Human_input 局部模块的冲突，解决方案：全局约束 Input函数，在gamerun为真时，不允许运行。*
```
if (!Sanguosha.gamerun) Sanguosha.Input(); 
```
* 待实现：完成关卡选择模块 & 相关说明 模块。