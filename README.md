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