/////////////////////////////////////////////////////////////////////////
///@system 新一代交易所系统
///@company 上海期货信息技术有限公司
///@file TraderApi.h
///@brief 定义了客户端接口
///@history 
///20060106	赵鸿昊		创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(TRADERAPI_H)
#define TRADERAPI_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ApiStruct.h"

#if defined(ISLIB) && defined(WIN32)
#ifdef LIB_TRADER_API_EXPORT
#define TRADER_API_EXPORT __declspec(dllexport)
#else
#define TRADER_API_EXPORT __declspec(dllimport)
#endif
#else
#define TRADER_API_EXPORT 
#endif

class TraderSpi
{
public:
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected(){};
	
	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};
		
	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse){};
	
	///客户端认证响应
	virtual void OnRspAuthenticate(RspAuthenticateField *pRspAuthenticateField, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};
	

	///登录请求响应
	virtual void OnRspUserLogin(RspUserLoginField *pRspUserLogin, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///登出请求响应
	virtual void OnRspUserLogout(UserLogoutField *pUserLogout, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///用户口令更新请求响应
	virtual void OnRspUserPasswordUpdate(UserPasswordUpdateField *pUserPasswordUpdate, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///资金账户口令更新请求响应
	virtual void OnRspTradingAccountPasswordUpdate(TradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单录入请求响应
	virtual void OnRspOrderInsert(InputOrderField *pInputOrder, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///预埋单录入请求响应
	virtual void OnRspParkedOrderInsert(ParkedOrderField *pParkedOrder, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///预埋撤单录入请求响应
	virtual void OnRspParkedOrderAction(ParkedOrderActionField *pParkedOrderAction, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单操作请求响应
	virtual void OnRspOrderAction(InputOrderActionField *pInputOrderAction, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///查询最大报单数量响应
	virtual void OnRspQueryMaxOrderVolume(QueryMaxOrderVolumeField *pQueryMaxOrderVolume, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///投资者结算结果确认响应
	virtual void OnRspSettlementInfoConfirm(SettlementInfoConfirmField *pSettlementInfoConfirm, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///删除预埋单响应
	virtual void OnRspRemoveParkedOrder(RemoveParkedOrderField *pRemoveParkedOrder, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///删除预埋撤单响应
	virtual void OnRspRemoveParkedOrderAction(RemoveParkedOrderActionField *pRemoveParkedOrderAction, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///执行宣告录入请求响应
	virtual void OnRspExecOrderInsert(InputExecOrderField *pInputExecOrder, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///执行宣告操作请求响应
	virtual void OnRspExecOrderAction(InputExecOrderActionField *pInputExecOrderAction, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///询价录入请求响应
	virtual void OnRspForQuoteInsert(InputForQuoteField *pInputForQuote, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报价录入请求响应
	virtual void OnRspQuoteInsert(InputQuoteField *pInputQuote, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报价操作请求响应
	virtual void OnRspQuoteAction(InputQuoteActionField *pInputQuoteAction, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///批量报单操作请求响应
	virtual void OnRspBatchOrderAction(InputBatchOrderActionField *pInputBatchOrderAction, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///申请组合录入请求响应
	virtual void OnRspCombActionInsert(InputCombActionField *pInputCombAction, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询报单响应
	virtual void OnRspQryOrder(OrderField *pOrder, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询成交响应
	virtual void OnRspQryTrade(TradeField *pTrade, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(InvestorPositionField *pInvestorPosition, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(TradingAccountField *pTradingAccount, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者响应
	virtual void OnRspQryInvestor(InvestorField *pInvestor, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易编码响应
	virtual void OnRspQryTradingCode(TradingCodeField *pTradingCode, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约保证金率响应
	virtual void OnRspQryInstrumentMarginRate(InstrumentMarginRateField *pInstrumentMarginRate, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约手续费率响应
	virtual void OnRspQryInstrumentCommissionRate(InstrumentCommissionRateField *pInstrumentCommissionRate, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易所响应
	virtual void OnRspQryExchange(ExchangeField *pExchange, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询产品响应
	virtual void OnRspQryProduct(ProductField *pProduct, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询合约响应
	virtual void OnRspQryInstrument(InstrumentField *pInstrument, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询行情响应
	virtual void OnRspQryDepthMarketData(DepthMarketDataField *pDepthMarketData, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者结算结果响应
	virtual void OnRspQrySettlementInfo(SettlementInfoField *pSettlementInfo, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询转帐银行响应
	virtual void OnRspQryTransferBank(TransferBankField *pTransferBank, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓明细响应
	virtual void OnRspQryInvestorPositionDetail(InvestorPositionDetailField *pInvestorPositionDetail, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询客户通知响应
	virtual void OnRspQryNotice(NoticeField *pNotice, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询结算信息确认响应
	virtual void OnRspQrySettlementInfoConfirm(SettlementInfoConfirmField *pSettlementInfoConfirm, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者持仓明细响应
	virtual void OnRspQryInvestorPositionCombineDetail(InvestorPositionCombineDetailField *pInvestorPositionCombineDetail, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///查询保证金监管系统经纪公司资金账户密钥响应
	virtual void OnRspQryCFMMCTradingAccountKey(CFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询仓单折抵信息响应
	virtual void OnRspQryEWarrantOffset(EWarrantOffsetField *pEWarrantOffset, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询投资者品种/跨品种保证金响应
	virtual void OnRspQryInvestorProductGroupMargin(InvestorProductGroupMarginField *pInvestorProductGroupMargin, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易所保证金率响应
	virtual void OnRspQryExchangeMarginRate(ExchangeMarginRateField *pExchangeMarginRate, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易所调整保证金率响应
	virtual void OnRspQryExchangeMarginRateAdjust(ExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询汇率响应
	virtual void OnRspQryExchangeRate(ExchangeRateField *pExchangeRate, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询二级代理操作员银期权限响应
	virtual void OnRspQrySecAgentACIDMap(SecAgentACIDMapField *pSecAgentACIDMap, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询产品报价汇率
	virtual void OnRspQryProductExchRate(ProductExchRateField *pProductExchRate, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询产品组
	virtual void OnRspQryProductGroup(ProductGroupField *pProductGroup, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询期权交易成本响应
	virtual void OnRspQryOptionInstrTradeCost(OptionInstrTradeCostField *pOptionInstrTradeCost, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询期权合约手续费响应
	virtual void OnRspQryOptionInstrCommRate(OptionInstrCommRateField *pOptionInstrCommRate, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询执行宣告响应
	virtual void OnRspQryExecOrder(ExecOrderField *pExecOrder, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询询价响应
	virtual void OnRspQryForQuote(ForQuoteField *pForQuote, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询报价响应
	virtual void OnRspQryQuote(QuoteField *pQuote, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询组合合约安全系数响应
	virtual void OnRspQryCombInstrumentGuard(CombInstrumentGuardField *pCombInstrumentGuard, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询申请组合响应
	virtual void OnRspQryCombAction(CombActionField *pCombAction, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询转帐流水响应
	virtual void OnRspQryTransferSerial(TransferSerialField *pTransferSerial, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询银期签约关系响应
	virtual void OnRspQryAccountregister(AccountregisterField *pAccountregister, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///错误应答
	virtual void OnRspError(RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///报单通知
	virtual void OnRtnOrder(OrderField *pOrder) {};

	///成交通知
	virtual void OnRtnTrade(TradeField *pTrade) {};

	///报单录入错误回报
	virtual void OnErrRtnOrderInsert(InputOrderField *pInputOrder, RspInfoField *pRspInfo) {};

	///报单操作错误回报
	virtual void OnErrRtnOrderAction(OrderActionField *pOrderAction, RspInfoField *pRspInfo) {};

	///合约交易状态通知
	virtual void OnRtnInstrumentStatus(InstrumentStatusField *pInstrumentStatus) {};

	///交易通知
	virtual void OnRtnTradingNotice(TradingNoticeInfoField *pTradingNoticeInfo) {};

	///提示条件单校验错误
	virtual void OnRtnErrorConditionalOrder(ErrorConditionalOrderField *pErrorConditionalOrder) {};

	///执行宣告通知
	virtual void OnRtnExecOrder(ExecOrderField *pExecOrder) {};

	///执行宣告录入错误回报
	virtual void OnErrRtnExecOrderInsert(InputExecOrderField *pInputExecOrder, RspInfoField *pRspInfo) {};

	///执行宣告操作错误回报
	virtual void OnErrRtnExecOrderAction(ExecOrderActionField *pExecOrderAction, RspInfoField *pRspInfo) {};

	///询价录入错误回报
	virtual void OnErrRtnForQuoteInsert(InputForQuoteField *pInputForQuote, RspInfoField *pRspInfo) {};

	///报价通知
	virtual void OnRtnQuote(QuoteField *pQuote) {};

	///报价录入错误回报
	virtual void OnErrRtnQuoteInsert(InputQuoteField *pInputQuote, RspInfoField *pRspInfo) {};

	///报价操作错误回报
	virtual void OnErrRtnQuoteAction(QuoteActionField *pQuoteAction, RspInfoField *pRspInfo) {};

	///询价通知
	virtual void OnRtnForQuoteRsp(ForQuoteRspField *pForQuoteRsp) {};

	///保证金监控中心用户令牌
	virtual void OnRtnCFMMCTradingAccountToken(CFMMCTradingAccountTokenField *pCFMMCTradingAccountToken) {};

	///批量报单操作错误回报
	virtual void OnErrRtnBatchOrderAction(BatchOrderActionField *pBatchOrderAction, RspInfoField *pRspInfo) {};

	///申请组合通知
	virtual void OnRtnCombAction(CombActionField *pCombAction) {};

	///申请组合录入错误回报
	virtual void OnErrRtnCombActionInsert(InputCombActionField *pInputCombAction, RspInfoField *pRspInfo) {};

	///请求查询签约银行响应
	virtual void OnRspQryContractBank(ContractBankField *pContractBank, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询预埋单响应
	virtual void OnRspQryParkedOrder(ParkedOrderField *pParkedOrder, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询预埋撤单响应
	virtual void OnRspQryParkedOrderAction(ParkedOrderActionField *pParkedOrderAction, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询交易通知响应
	virtual void OnRspQryTradingNotice(TradingNoticeField *pTradingNotice, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询经纪公司交易参数响应
	virtual void OnRspQryBrokerTradingParams(BrokerTradingParamsField *pBrokerTradingParams, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询经纪公司交易算法响应
	virtual void OnRspQryBrokerTradingAlgos(BrokerTradingAlgosField *pBrokerTradingAlgos, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///请求查询监控中心用户令牌
	virtual void OnRspQueryCFMMCTradingAccountToken(QueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///银行发起银行资金转期货通知
	virtual void OnRtnFromBankToFutureByBank(RspTransferField *pRspTransfer) {};

	///银行发起期货资金转银行通知
	virtual void OnRtnFromFutureToBankByBank(RspTransferField *pRspTransfer) {};

	///银行发起冲正银行转期货通知
	virtual void OnRtnRepealFromBankToFutureByBank(RspRepealField *pRspRepeal) {};

	///银行发起冲正期货转银行通知
	virtual void OnRtnRepealFromFutureToBankByBank(RspRepealField *pRspRepeal) {};

	///期货发起银行资金转期货通知
	virtual void OnRtnFromBankToFutureByFuture(RspTransferField *pRspTransfer) {};

	///期货发起期货资金转银行通知
	virtual void OnRtnFromFutureToBankByFuture(RspTransferField *pRspTransfer) {};

	///系统运行时期货端手工发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	virtual void OnRtnRepealFromBankToFutureByFutureManual(RspRepealField *pRspRepeal) {};

	///系统运行时期货端手工发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	virtual void OnRtnRepealFromFutureToBankByFutureManual(RspRepealField *pRspRepeal) {};

	///期货发起查询银行余额通知
	virtual void OnRtnQueryBankBalanceByFuture(NotifyQueryAccountField *pNotifyQueryAccount) {};

	///期货发起银行资金转期货错误回报
	virtual void OnErrRtnBankToFutureByFuture(ReqTransferField *pReqTransfer, RspInfoField *pRspInfo) {};

	///期货发起期货资金转银行错误回报
	virtual void OnErrRtnFutureToBankByFuture(ReqTransferField *pReqTransfer, RspInfoField *pRspInfo) {};

	///系统运行时期货端手工发起冲正银行转期货错误回报
	virtual void OnErrRtnRepealBankToFutureByFutureManual(ReqRepealField *pReqRepeal, RspInfoField *pRspInfo) {};

	///系统运行时期货端手工发起冲正期货转银行错误回报
	virtual void OnErrRtnRepealFutureToBankByFutureManual(ReqRepealField *pReqRepeal, RspInfoField *pRspInfo) {};

	///期货发起查询银行余额错误回报
	virtual void OnErrRtnQueryBankBalanceByFuture(ReqQueryAccountField *pReqQueryAccount, RspInfoField *pRspInfo) {};

	///期货发起冲正银行转期货请求，银行处理完毕后报盘发回的通知
	virtual void OnRtnRepealFromBankToFutureByFuture(RspRepealField *pRspRepeal) {};

	///期货发起冲正期货转银行请求，银行处理完毕后报盘发回的通知
	virtual void OnRtnRepealFromFutureToBankByFuture(RspRepealField *pRspRepeal) {};

	///期货发起银行资金转期货应答
	virtual void OnRspFromBankToFutureByFuture(ReqTransferField *pReqTransfer, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///期货发起期货资金转银行应答
	virtual void OnRspFromFutureToBankByFuture(ReqTransferField *pReqTransfer, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///期货发起查询银行余额应答
	virtual void OnRspQueryBankAccountMoneyByFuture(ReqQueryAccountField *pReqQueryAccount, RspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///银行发起银期开户通知
	virtual void OnRtnOpenAccountByBank(OpenAccountField *pOpenAccount) {};

	///银行发起银期销户通知
	virtual void OnRtnCancelAccountByBank(CancelAccountField *pCancelAccount) {};

	///银行发起变更银行账号通知
	virtual void OnRtnChangeAccountByBank(ChangeAccountField *pChangeAccount) {};
};

class TRADER_API_EXPORT TraderApi
{
public:
	///创建TraderApi
	///@param pszFlowPath 存贮订阅信息文件的目录，默认为当前目录
	///@return 创建出的UserApi
	static TraderApi *CreateTraderApi(const char *pszFlowPath = "");
	
	///获取API的版本信息
	///@retrun 获取到的版本号
	static const char *GetApiVersion();
	
	///删除接口对象本身
	///@remark 不再使用本接口对象时,调用该函数删除接口对象
	virtual void Release() = 0;
	
	///初始化
	///@remark 初始化运行环境,只有调用后,接口才开始工作
	virtual void Init() = 0;
	
	///等待接口线程结束运行
	///@return 线程退出代码
	virtual int Join() = 0;
	
	///获取当前交易日
	///@retrun 获取到的交易日
	///@remark 只有登录成功后,才能得到正确的交易日
	virtual const char *GetTradingDay() = 0;
	
	///注册前置机网络地址
	///@param pszFrontAddress：前置机网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:17001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”17001”代表服务器端口号。
	virtual void RegisterFront(char *pszFrontAddress) = 0;
	
	///注册名字服务器网络地址
	///@param pszNsAddress：名字服务器网络地址。
	///@remark 网络地址的格式为：“protocol://ipaddress:port”，如：”tcp://127.0.0.1:12001”。 
	///@remark “tcp”代表传输协议，“127.0.0.1”代表服务器地址。”12001”代表服务器端口号。
	///@remark RegisterNameServer优先于RegisterFront
	virtual void RegisterNameServer(char *pszNsAddress) = 0;
	
	///注册名字服务器用户信息
	///@param pFensUserInfo：用户信息。
	virtual void RegisterFensUserInfo(FensUserInfoField * pFensUserInfo) = 0;
	
	///注册回调接口
	///@param pSpi 派生自回调接口类的实例
	virtual void RegisterSpi(TraderSpi *pSpi) = 0;
	
	///订阅私有流。
	///@param nResumeType 私有流重传方式  
	///        TERT_RESTART:从本交易日开始重传
	///        TERT_RESUME:从上次收到的续传
	///        TERT_QUICK:只传送登录后私有流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到私有流的数据。
	virtual void SubscribePrivateTopic(TE_RESUME_TYPE nResumeType) = 0;
	
	///订阅公共流。
	///@param nResumeType 公共流重传方式  
	///        TERT_RESTART:从本交易日开始重传
	///        TERT_RESUME:从上次收到的续传
	///        TERT_QUICK:只传送登录后公共流的内容
	///@remark 该方法要在Init方法前调用。若不调用则不会收到公共流的数据。
	virtual void SubscribePublicTopic(TE_RESUME_TYPE nResumeType) = 0;

	///客户端认证请求
	virtual int ReqAuthenticate(ReqAuthenticateField *pReqAuthenticateField, int nRequestID) = 0;

	///用户登录请求
	virtual int ReqUserLogin(ReqUserLoginField *pReqUserLoginField, int nRequestID) = 0;
	

	///登出请求
	virtual int ReqUserLogout(UserLogoutField *pUserLogout, int nRequestID) = 0;

	///用户口令更新请求
	virtual int ReqUserPasswordUpdate(UserPasswordUpdateField *pUserPasswordUpdate, int nRequestID) = 0;

	///资金账户口令更新请求
	virtual int ReqTradingAccountPasswordUpdate(TradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID) = 0;

	///报单录入请求
	virtual int ReqOrderInsert(InputOrderField *pInputOrder, int nRequestID) = 0;

	///预埋单录入请求
	virtual int ReqParkedOrderInsert(ParkedOrderField *pParkedOrder, int nRequestID) = 0;

	///预埋撤单录入请求
	virtual int ReqParkedOrderAction(ParkedOrderActionField *pParkedOrderAction, int nRequestID) = 0;

	///报单操作请求
	virtual int ReqOrderAction(InputOrderActionField *pInputOrderAction, int nRequestID) = 0;

	///查询最大报单数量请求
	virtual int ReqQueryMaxOrderVolume(QueryMaxOrderVolumeField *pQueryMaxOrderVolume, int nRequestID) = 0;

	///投资者结算结果确认
	virtual int ReqSettlementInfoConfirm(SettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID) = 0;

	///请求删除预埋单
	virtual int ReqRemoveParkedOrder(RemoveParkedOrderField *pRemoveParkedOrder, int nRequestID) = 0;

	///请求删除预埋撤单
	virtual int ReqRemoveParkedOrderAction(RemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID) = 0;

	///执行宣告录入请求
	virtual int ReqExecOrderInsert(InputExecOrderField *pInputExecOrder, int nRequestID) = 0;

	///执行宣告操作请求
	virtual int ReqExecOrderAction(InputExecOrderActionField *pInputExecOrderAction, int nRequestID) = 0;

	///询价录入请求
	virtual int ReqForQuoteInsert(InputForQuoteField *pInputForQuote, int nRequestID) = 0;

	///报价录入请求
	virtual int ReqQuoteInsert(InputQuoteField *pInputQuote, int nRequestID) = 0;

	///报价操作请求
	virtual int ReqQuoteAction(InputQuoteActionField *pInputQuoteAction, int nRequestID) = 0;

	///批量报单操作请求
	virtual int ReqBatchOrderAction(InputBatchOrderActionField *pInputBatchOrderAction, int nRequestID) = 0;

	///申请组合录入请求
	virtual int ReqCombActionInsert(InputCombActionField *pInputCombAction, int nRequestID) = 0;

	///请求查询报单
	virtual int ReqQryOrder(QryOrderField *pQryOrder, int nRequestID) = 0;

	///请求查询成交
	virtual int ReqQryTrade(QryTradeField *pQryTrade, int nRequestID) = 0;

	///请求查询投资者持仓
	virtual int ReqQryInvestorPosition(QryInvestorPositionField *pQryInvestorPosition, int nRequestID) = 0;

	///请求查询资金账户
	virtual int ReqQryTradingAccount(QryTradingAccountField *pQryTradingAccount, int nRequestID) = 0;

	///请求查询投资者
	virtual int ReqQryInvestor(QryInvestorField *pQryInvestor, int nRequestID) = 0;

	///请求查询交易编码
	virtual int ReqQryTradingCode(QryTradingCodeField *pQryTradingCode, int nRequestID) = 0;

	///请求查询合约保证金率
	virtual int ReqQryInstrumentMarginRate(QryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID) = 0;

	///请求查询合约手续费率
	virtual int ReqQryInstrumentCommissionRate(QryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID) = 0;

	///请求查询交易所
	virtual int ReqQryExchange(QryExchangeField *pQryExchange, int nRequestID) = 0;

	///请求查询产品
	virtual int ReqQryProduct(QryProductField *pQryProduct, int nRequestID) = 0;

	///请求查询合约
	virtual int ReqQryInstrument(QryInstrumentField *pQryInstrument, int nRequestID) = 0;

	///请求查询行情
	virtual int ReqQryDepthMarketData(QryDepthMarketDataField *pQryDepthMarketData, int nRequestID) = 0;

	///请求查询投资者结算结果
	virtual int ReqQrySettlementInfo(QrySettlementInfoField *pQrySettlementInfo, int nRequestID) = 0;

	///请求查询转帐银行
	virtual int ReqQryTransferBank(QryTransferBankField *pQryTransferBank, int nRequestID) = 0;

	///请求查询投资者持仓明细
	virtual int ReqQryInvestorPositionDetail(QryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID) = 0;

	///请求查询客户通知
	virtual int ReqQryNotice(QryNoticeField *pQryNotice, int nRequestID) = 0;

	///请求查询结算信息确认
	virtual int ReqQrySettlementInfoConfirm(QrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID) = 0;

	///请求查询投资者持仓明细
	virtual int ReqQryInvestorPositionCombineDetail(QryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID) = 0;

	///请求查询保证金监管系统经纪公司资金账户密钥
	virtual int ReqQryCFMMCTradingAccountKey(QryCFMMCTradingAccountKeyField *pQryCFMMCTradingAccountKey, int nRequestID) = 0;

	///请求查询仓单折抵信息
	virtual int ReqQryEWarrantOffset(QryEWarrantOffsetField *pQryEWarrantOffset, int nRequestID) = 0;

	///请求查询投资者品种/跨品种保证金
	virtual int ReqQryInvestorProductGroupMargin(QryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin, int nRequestID) = 0;

	///请求查询交易所保证金率
	virtual int ReqQryExchangeMarginRate(QryExchangeMarginRateField *pQryExchangeMarginRate, int nRequestID) = 0;

	///请求查询交易所调整保证金率
	virtual int ReqQryExchangeMarginRateAdjust(QryExchangeMarginRateAdjustField *pQryExchangeMarginRateAdjust, int nRequestID) = 0;

	///请求查询汇率
	virtual int ReqQryExchangeRate(QryExchangeRateField *pQryExchangeRate, int nRequestID) = 0;

	///请求查询二级代理操作员银期权限
	virtual int ReqQrySecAgentACIDMap(QrySecAgentACIDMapField *pQrySecAgentACIDMap, int nRequestID) = 0;

	///请求查询产品报价汇率
	virtual int ReqQryProductExchRate(QryProductExchRateField *pQryProductExchRate, int nRequestID) = 0;

	///请求查询产品组
	virtual int ReqQryProductGroup(QryProductGroupField *pQryProductGroup, int nRequestID) = 0;

	///请求查询期权交易成本
	virtual int ReqQryOptionInstrTradeCost(QryOptionInstrTradeCostField *pQryOptionInstrTradeCost, int nRequestID) = 0;

	///请求查询期权合约手续费
	virtual int ReqQryOptionInstrCommRate(QryOptionInstrCommRateField *pQryOptionInstrCommRate, int nRequestID) = 0;

	///请求查询执行宣告
	virtual int ReqQryExecOrder(QryExecOrderField *pQryExecOrder, int nRequestID) = 0;

	///请求查询询价
	virtual int ReqQryForQuote(QryForQuoteField *pQryForQuote, int nRequestID) = 0;

	///请求查询报价
	virtual int ReqQryQuote(QryQuoteField *pQryQuote, int nRequestID) = 0;

	///请求查询组合合约安全系数
	virtual int ReqQryCombInstrumentGuard(QryCombInstrumentGuardField *pQryCombInstrumentGuard, int nRequestID) = 0;

	///请求查询申请组合
	virtual int ReqQryCombAction(QryCombActionField *pQryCombAction, int nRequestID) = 0;

	///请求查询转帐流水
	virtual int ReqQryTransferSerial(QryTransferSerialField *pQryTransferSerial, int nRequestID) = 0;

	///请求查询银期签约关系
	virtual int ReqQryAccountregister(QryAccountregisterField *pQryAccountregister, int nRequestID) = 0;

	///请求查询签约银行
	virtual int ReqQryContractBank(QryContractBankField *pQryContractBank, int nRequestID) = 0;

	///请求查询预埋单
	virtual int ReqQryParkedOrder(QryParkedOrderField *pQryParkedOrder, int nRequestID) = 0;

	///请求查询预埋撤单
	virtual int ReqQryParkedOrderAction(QryParkedOrderActionField *pQryParkedOrderAction, int nRequestID) = 0;

	///请求查询交易通知
	virtual int ReqQryTradingNotice(QryTradingNoticeField *pQryTradingNotice, int nRequestID) = 0;

	///请求查询经纪公司交易参数
	virtual int ReqQryBrokerTradingParams(QryBrokerTradingParamsField *pQryBrokerTradingParams, int nRequestID) = 0;

	///请求查询经纪公司交易算法
	virtual int ReqQryBrokerTradingAlgos(QryBrokerTradingAlgosField *pQryBrokerTradingAlgos, int nRequestID) = 0;

	///请求查询监控中心用户令牌
	virtual int ReqQueryCFMMCTradingAccountToken(QueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, int nRequestID) = 0;

	///期货发起银行资金转期货请求
	virtual int ReqFromBankToFutureByFuture(ReqTransferField *pReqTransfer, int nRequestID) = 0;

	///期货发起期货资金转银行请求
	virtual int ReqFromFutureToBankByFuture(ReqTransferField *pReqTransfer, int nRequestID) = 0;

	///期货发起查询银行余额请求
	virtual int ReqQueryBankAccountMoneyByFuture(ReqQueryAccountField *pReqQueryAccount, int nRequestID) = 0;
protected:
	~TraderApi(){};
};

#endif
