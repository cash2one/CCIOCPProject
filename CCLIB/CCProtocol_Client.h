/**************************************************************************************
@author: 陈昌
@content: 游戏客户端与服务器间通信的常量和结构定义
**************************************************************************************/

#ifndef __CC_PROTOCOL_CLIENT_H__
#define __CC_PROTOCOL_CLIENT_H__

//这里使用1字节对齐
#pragma pack(1)

// Client与服务器间的通讯头
typedef struct _TClientSocketHead
{
	unsigned int uiSign;				// 分隔符 CS_SEGMENTATION_SIGN
	unsigned short usPackageLen;		// 封包总长度
	unsigned short usIdent;				// Ident or $8000 = 压缩   [Ident>=$8000 数据头后2字节表示压缩前数据长度，后续数据为压缩数据区。Ident<$8000 数据头后为数据区]
	unsigned int uiIdx;		    	    // 包序号,后续数据可能会被压缩
}TClientSocketHead, *PClientSocketHead;

// 动作类型
enum TActionType{
	acNone = 0,
	acStand,
	acWalk,
	acRun,
	acJump,
	acRush,
	acBackStep,
	acAttack1,
	acAttack2,
	acMagic1,
	acMagic2,
	acShoot1,
	acShoot2,
	acAttack0,
	acAttacked,
	acDie,
	acStone,
	acBorn,
	acLRush,
	acRRush,
	acIconSmall,
	acIconBig,
	acstepBack
};

//客户端的窗口类型
enum TClientWindowType{
	cwInValid = 0,                                          // 无效窗口
	cwAuthenWindow = 1,                                     // 登录认证窗口
	cwWarRule,                                              // 同意对战协议窗口
	cwQueue,                                                // 排队窗口
	cwCreateRole,                                           // 创建角色窗口
	cwMessageBox,                                           // 弹出窗口
	cwDialog,
	cwNotice,                                               // 文明公约
	cwDealRequest,                                          // 交易请求提示框
	cwDealDialog,                                           // 交易框
	cwVerifyCode,                                           // 验证码窗口
	cwReLive,                                               // 复活窗口
	cwTransDialog,                                          // 事务窗口，这类型的窗口确认返回时必须将TransID原样返回
	/*
		cwTransDialog类型窗口具体说明：
		SCM_OPEN_WINDOW：Param 0:确认框 1：输入框 2 : 2个输入框
						 TransID：事务ID，TClientWindowRec结构后为提示信息
		CM_CLOSE_WINDOW：Param 0 : 取消   1：确认 TransID：事务ID，若是输入框TClientWindowRec结构后为输入内容
	*/

	cwScriptDialog,                                         // 脚本对话框
	cwNpcItemOper,                                          // Npc对单独物品的操作窗口
	/*
		cwNpcItemOper类型窗口具体说明：
		Param : 1 物品修理窗口
	*/

	cwNpcShop,                                              // Npc商店窗口
	cwIMTransDialog,                                        // IMServer弹出对话框
	cwStorage,                                              // 仓库窗口
	cwMonCry,                                               // 怪物说话
	/*
		cwMonCry类型窗口具体说明：
		Param: 头像索引
		TransID : 音效索引
		buf : 说话内容
	*/

	cwCopyHint,                                             // 副本提示
	/*
		cwCopyHint类型窗口具体说明：
		Param: 副本ID
	    TransID : 0 : 开启 1 : 通过 2：失败
	    buf : 提示信息
	*/

	cwColdTime,                                             // 倒计时
	/*
		cwColdTime类型窗口具体说明：
		Param:倒计时时长
		TransID : 倒计时类型ID
		buf : 倒计时提示
	*/

	cwWeaponUpgrade,                                        // 武器升级
	cwGuildSet,                                             // 行会设置界面
	cwYBDeal,                                               // 元宝交易框
	cwGridData,                                             // 网格数据窗口
	/*
		cwGridData类型窗口具体说明：
		Param:TGridType
		buf : 窗口定义数据
	*/

	cwSafeCard,                                             //密保卡认证
	/*
	    cwSafeCard类型窗口具体说明：
		SCM_OPEN_WINDOW
		param : 为3个矩阵值
		CM_CLOSE_WINDOW : 
		BUF : 为3个矩阵对应输入值字符串
	*/

	cwPayPwd,                                               // 支付密码
	cwWeaponMelting,                                        // 武器熔炼
	cwRoleReName,                                           // 角色重命名
	cwHopePool,                                             // 许愿池
	cwEmail,                                                // 邮件框
	cwPlayerShop,                                           // 玩家商铺
	cwBag,                                                  // 背包
	cwYearCeremony                                          // 年度盛典
};

// SCM_AUTHEN_RESULT
typedef struct _TAuthenResponse
{
	int iResult;   //1 成功 其他 失败                                      
	//------------------------
	//------------------------
	//--- int64怎么定义比较好
	_int64 dbLastLoginTime;
	char szUniqueID[ACCOUNT_MAX_LEN];
	char szLastLoginIP[IP_ADDRESS_MAX_LEN+1];
	char szMsg[51];
	char szLoginIP[IP_ADDRESS_MAX_LEN + 1];
}TAuthenResponse, *PAuthenResponse;

// CM_SELECT_SERVER
typedef struct _TCMSelectServer
{
	int iMaskServerID;				 // 选择的对外的服务器号
	int iCheckIP;                    // 所解析的 固定域名的 地址，用以区分不同的网络类型
}TCMSelectServer, *PCMSelectServer;

// CM_CLOSE_WINDOW、SCM_OPEN_WINDOW、SCM_CLOSE_WINDOW
typedef struct _TClientWindowRec
{
	unsigned char WinType;
	int Param;
	unsigned int TransID;          // 事务ID
	//buf:提示信息字符串
}TClientWindowRec, *PClientWindowRec;

// SCM_SELECT_AREA
typedef struct _TNextGateInfo
{
	int iSessionID;
	int iGateAddr;
	int iGatePort;
}TNextGateInfo, *PNextGateInfo;

// SCM_ACTFAIL
typedef struct _TPkgActFail
{
	int iObjID;
	unsigned short usX;
	unsigned short usY;
	unsigned char ucDir;
	unsigned short usAct;
}TPkgActFail, *PPkgActFail;

// SCM_ACTGOOD
typedef struct _TPkgActGood
{
	int iObjID;						//执行对象ID
	unsigned short usAct;			//执行动作
	unsigned short usParam;			//执行参数，若是技能则为技能ID
}TPkgActGood, *PPkgActGood;

// CM_WALK, CM_RUN, CM_TURN、SCM_WALK, SCM_RUN、 SCM_TURN、SCM_RUSH、SCM_BACKSTEP
typedef struct _TPkgAction
{
	int iObjID;
	unsigned short usX;
	unsigned short usY;
	unsigned char ucDir;
}TPkgAction, *PPkgAction;

// SCM_MAPINFO
typedef struct _TPkgMapInfo
{
	int iMapID;
	int iFileID;
	int iMapObjID;    //场景对象ID
	char szMapDesc[MAP_NAME_MAX_LEN];
}TPkgMapInfo, *PPkgMapInfo;

// SCM_CDTIME_UPDATE
typedef struct _TPkgCDTimeChg
{
	unsigned char ucCDType;
	unsigned int uiCDTime;
}TPkgCDTimeChg, *PPkgCDTimeChg;

//	SCM_SYSTEM_MESSAGE
enum TMesssageType{
	//系统公告、组队消息、行会消息、私聊消息、滚动消息、提示框消息、
	msSystem = 0, msGroup, msGuild, msWhisper, msRoll, msDialog,
	//怪物冒泡、附近喊话(白字)、家族、喇叭喊话、提示信息、左侧边条消息，中央消息、系统红字公告(带喇叭)、调试信息
	msMonster, msCry, msClan, msLoudSpeaker, msHint, msLeftSide, msCenter, msGMSystem, msDebug
};
//bMsgType=msLeftSide时 nObjID表示类型，具体类型见战斗信息分类定义
//bMsgType=msLoudSpeaker时 nObjID表示类型，0:普通喇叭 1：顶行显示喇叭


//行会操作通用结构，对应字段意义与OpID为子协议号挂钩
typedef struct _TPkgGuildOpRec
{
	char strOpStr1[GUILD_OP_MAX_LEN];
	unsigned char ucOpID;
	int iParam;
}TPkgGuildOpRec, *PPkgGuildOpRec;


#pragma pack()



const int CS_SEGMENTATION_CLIENTSIGN = 0XAABBCCDD;          // 游戏客户端和服务器间通讯协议起始标志

//游戏客户端发送给服务器的消息
const int CM_PING = 10;										 // 心跳
const int CM_SELECT_SERVER_OLD = 11;						 // 旧版选服协议
const int CM_GAME_CONNECT = 12;								 // 连接到GameGate
const int CM_CLOSE_WINDOW = 14;                              // 关闭窗体
const int CM_GAME_QUEUE = 15;                                // 查询队列
const int CM_REGIST_REQUEST = 17;                            // 新建帐号
const int CM_VERIFY_CODE = 18;                               // 提交验证码
const int CM_NEXT_VERIFY_CODE = 19;                          // 下一张验证码
const int CM_LOGON_OK = 21;                                  // 进入游戏ok
const int CM_RUSH = 99;										 // 前冲
const int CM_QUIT = 100;									 // 正常退出

//游戏客户端部分重要消息的重新编号
const int CM_SELECT_SERVER = 3011;                           // 选服协议
const int CM_AUTHEN_REQUEST = 3013;                          // 认证请求
const int CM_CREATE_ROLE = 3016;                             // 创建角色
const int CM_ENTER_GAMESCENE = 3020;                         // 进入游戏
const int CM_GPS_CHECK_RESPONSE = 4100;                      // 反外挂，数据包返回
const int CM_WALK = 4101;                                    //走
const int CM_RUN = 4102;                                     //跑
const int CM_PHYHIT = 4103;                                  //物理攻击
const int CM_SPELL = 4104;                                   //魔法攻击
const int CM_SAY = 4107;                                     //客户端发送聊天信息
const int CM_PICKUP = 4108;                                  //拾取物品
const int CM_CLICK_NPC = 4115;                               //点击NPC
const int CM_CLICK_NPC_OPTION = 4116;                        //点击NPC对话框中的选项
const int CM_USE_BAG_ITEM = 4117;                            //客户端双击使用背包物品
const int CM_QUESTION_DETAIL_REQ = 4118;                     //客户端请求答题信息
const int CM_QUESTION_ANSWER = 4119;                         //回答问题
const int CM_PWDPROTECT_CHG = 4120;                          //二级密码保护状态切换

//服务器端发给游戏客户端的消息

const int SCM_AUTHEN_RESULT = 13;                           // 认证
const int SCM_OPEN_WINDOW = 14;                             // 开启窗口
const int SCM_CLOSE_WINDOW = 15;                            // 服务端请求关闭窗口
const int SCM_RESSERVER_INFO = 18;                          // 资源服务器的IP
const int SCM_ROLE_INFO = 19;                               // 角色信息
const int SCM_QUIT = 20;                                    // 退出


const int SCM_MAPINFO = 100;                                // 地图信息
const int SCM_SKILL_LIST = 102;                             // 技能列表
const int SCM_SKILL_ADD = 103;                              // 更新技能信息，若是不存在则添加


const int SCM_ACTGOOD = 209;                                // 执行成功
const int SCM_ACTFAIL = 210;                                // 执行失败
const int SCM_DIE = 214;                                    // 死亡  
const int SCM_BACKSTEP = 216;                               // 后退
const int SCM_JUMP = 220;                                   //跳
const int SCM_L_RUSH = 221;                                 //前冲(左脚)
const int SCM_R_RUSH = 222;                                 //前冲(右脚)


const int SCM_CDTIME_UPDATE = 312;                          // CD更新

const int SCM_RELIVE = 318;                                 // 复活



const int SCM_ENCODE = 5008;                                 // 编码
const int SCM_DECODE = 5009;                                 // 解码
const int SCM_SELECT_AREA = 5011;                            // 选区
const int SCM_SYSTEM_MESSAGE = 5017;                         // 消息
const int SCM_CAN_ENTER = 5022;                              // 可以进入游戏
const int SCM_GPS_CHECK_REQUEST = 6100;                      // 反外挂检查
const int SCM_LOGON = 6101;                                  // 主角进入游戏
const int SCM_APPEAR = 6202;                                 // NPC出现
const int SCM_HUMAN_APPEAR = 6203;                           // 角色出现
const int SCM_ITEM_APPEAR = 6204;                            // 地图掉物出现
const int SCM_HP_CHANGE = 6300;                              // 其他目标的健康值改变


//其它常量定义

const int ENCODE_START_LEN = 6;

//共享CD定义
const int CD_DENY = 0;										 //禁止
const int CD_NOT_DELAY = 1;                                  //普通(即无CD)
const int CD_ATTACK = 2;									 //物理攻击公共CD ID
const int CD_MAGIC = 3;										 //魔法攻击公共CD ID
const int CD_MOVE = 4;										 //位移公共CD ID
const int CD_SAY = 5;										 //喊话CD
const int CD_CLICK_NPC = 6;                                  //点击NPC
const int CD_USEITEM = 7;                                    //使用物品
const int CD_RELATION_OP = 8;                                //关系操作
const int CD_RUSH = 9;										 //前冲CD
const int CD_EMAIL = 250;									 //邮件



#endif //__CC_PROTOCOL_CLIENT_H__