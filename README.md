# QSanguosha
support by SFML &amp; C++  
## 2020.4.7 开发思路  
* 思考：就是 引入 按钮 确定 取消 结束   ——和 设置 目标要关联起来o    以便以后 国战  单机多人   
* 思考：技能怎么引入是个大问题  加个技能类》》又不能引入别的参数   不知道加players 的类行不行  已知 game 类不行  
## 2020.4.8 开发思路  
*已解决：新增按钮类，按钮已经实现了基础框架——不同情况下可用or变黑，悬浮加亮  
*已解决：回合期间 击中牌可锁定目标了，并且在》类player下新增判断变量 bool select_card 判断当前是否选择卡牌来呈现 选择&非选择动画  
*已解决：锁定目标结合了 card_info下的 bool can_attack变量判断，这个在 pile_card 类中使用 bool card_can_attack(int number) 实现转变   
* 待实现：合理应用input ,每次执行只返回 vector 所有操作在 logic 中 也就是huanm_round,目前局限为仅能使用一次input，此后尝试将 input 置于 游戏逻辑外 将 human_round & machine_round 结合为logic   
* 待实现：按钮实现点击特效并且 打出牌 更新游戏状态   
* 待实现：重大难题——攻克游戏技能施展？在哪施展？目前已知 skill 可以引入player类！放入game类？ 下次code的着重点—— huamn_round 杀后，machine 闪 实现！
