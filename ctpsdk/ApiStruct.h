/////////////////////////////////////////////////////////////////////////
///@system 新一代交易所系统
///@company 上海期货信息技术有限公司
///@file ApiStruct.h
///@brief 定义了客户端接口使用的业务数据结构
///@history 
///20060106	赵鸿昊		创建该文件
/////////////////////////////////////////////////////////////////////////

#if !defined(APISTRUCT_H)
#define APISTRUCT_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ApiDataType.h"

///信息分发
struct DisseminationField
{
	///序列系列号
	SequenceSeriesType	SequenceSeries;
	///序列号
	SequenceNoType	SequenceNo;
};

///用户登录请求
struct ReqUserLoginField
{
	///交易日
	DateType	TradingDay;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///密码
	PasswordType	Password;
	///用户端产品信息
	ProductInfoType	UserProductInfo;
	///接口端产品信息
	ProductInfoType	InterfaceProductInfo;
	///协议信息
	ProtocolInfoType	ProtocolInfo;
	///Mac地址
	MacAddressType	MacAddress;
	///动态密码
	PasswordType	OneTimePassword;
	///终端IP地址
	IPAddressType	ClientIPAddress;
};

///用户登录应答
struct RspUserLoginField
{
	///交易日
	DateType	TradingDay;
	///登录成功时间
	TimeType	LoginTime;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///交易系统名称
	SystemNameType	SystemName;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///最大报单引用
	OrderRefType	MaxOrderRef;
	///上期所时间
	TimeType	SHFETime;
	///大商所时间
	TimeType	DCETime;
	///郑商所时间
	TimeType	CZCETime;
	///中金所时间
	TimeType	FFEXTime;
	///能源中心时间
	TimeType	INETime;
};

///用户登出请求
struct UserLogoutField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
};

///强制交易员退出
struct ForceUserLogoutField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
};

///客户端认证请求
struct ReqAuthenticateField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///用户端产品信息
	ProductInfoType	UserProductInfo;
	///认证码
	AuthCodeType	AuthCode;
};

///客户端认证响应
struct RspAuthenticateField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///用户端产品信息
	ProductInfoType	UserProductInfo;
};

///客户端认证信息
struct AuthenticationInfoField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///用户端产品信息
	ProductInfoType	UserProductInfo;
	///认证信息
	AuthInfoType	AuthInfo;
	///是否为认证结果
	BoolType	IsResult;
};

///银期转帐报文头
struct TransferHeaderField
{
	///版本号，常量，1.0
	VersionType	Version;
	///交易代码，必填
	TradeCodeType	TradeCode;
	///交易日期，必填，格式：yyyymmdd
	TradeDateType	TradeDate;
	///交易时间，必填，格式：hhmmss
	TradeTimeType	TradeTime;
	///发起方流水号，N/A
	TradeSerialType	TradeSerial;
	///期货公司代码，必填
	FutureIDType	FutureID;
	///银行代码，根据查询银行得到，必填
	BankIDType	BankID;
	///银行分中心代码，根据查询银行得到，必填
	BankBrchIDType	BankBrchID;
	///操作员，N/A
	OperNoType	OperNo;
	///交易设备类型，N/A
	DeviceIDType	DeviceID;
	///记录数，N/A
	RecordNumType	RecordNum;
	///会话编号，N/A
	SessionIDType	SessionID;
	///请求编号，N/A
	RequestIDType	RequestID;
};

///银行资金转期货请求，TradeCode=202001
struct TransferBankToFutureReqField
{
	///期货资金账户
	AccountIDType	FutureAccount;
	///密码标志
	FuturePwdFlagType	FuturePwdFlag;
	///密码
	FutureAccPwdType	FutureAccPwd;
	///转账金额
	MoneyType	TradeAmt;
	///客户手续费
	MoneyType	CustFee;
	///币种：RMB-人民币 USD-美圆 HKD-港元
	CurrencyCodeType	CurrencyCode;
};

///银行资金转期货请求响应
struct TransferBankToFutureRspField
{
	///响应代码
	RetCodeType	RetCode;
	///响应信息
	RetInfoType	RetInfo;
	///资金账户
	AccountIDType	FutureAccount;
	///转帐金额
	MoneyType	TradeAmt;
	///应收客户手续费
	MoneyType	CustFee;
	///币种
	CurrencyCodeType	CurrencyCode;
};

///期货资金转银行请求，TradeCode=202002
struct TransferFutureToBankReqField
{
	///期货资金账户
	AccountIDType	FutureAccount;
	///密码标志
	FuturePwdFlagType	FuturePwdFlag;
	///密码
	FutureAccPwdType	FutureAccPwd;
	///转账金额
	MoneyType	TradeAmt;
	///客户手续费
	MoneyType	CustFee;
	///币种：RMB-人民币 USD-美圆 HKD-港元
	CurrencyCodeType	CurrencyCode;
};

///期货资金转银行请求响应
struct TransferFutureToBankRspField
{
	///响应代码
	RetCodeType	RetCode;
	///响应信息
	RetInfoType	RetInfo;
	///资金账户
	AccountIDType	FutureAccount;
	///转帐金额
	MoneyType	TradeAmt;
	///应收客户手续费
	MoneyType	CustFee;
	///币种
	CurrencyCodeType	CurrencyCode;
};

///查询银行资金请求，TradeCode=204002
struct TransferQryBankReqField
{
	///期货资金账户
	AccountIDType	FutureAccount;
	///密码标志
	FuturePwdFlagType	FuturePwdFlag;
	///密码
	FutureAccPwdType	FutureAccPwd;
	///币种：RMB-人民币 USD-美圆 HKD-港元
	CurrencyCodeType	CurrencyCode;
};

///查询银行资金请求响应
struct TransferQryBankRspField
{
	///响应代码
	RetCodeType	RetCode;
	///响应信息
	RetInfoType	RetInfo;
	///资金账户
	AccountIDType	FutureAccount;
	///银行余额
	MoneyType	TradeAmt;
	///银行可用余额
	MoneyType	UseAmt;
	///银行可取余额
	MoneyType	FetchAmt;
	///币种
	CurrencyCodeType	CurrencyCode;
};

///查询银行交易明细请求，TradeCode=204999
struct TransferQryDetailReqField
{
	///期货资金账户
	AccountIDType	FutureAccount;
};

///查询银行交易明细请求响应
struct TransferQryDetailRspField
{
	///交易日期
	DateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///交易代码
	TradeCodeType	TradeCode;
	///期货流水号
	TradeSerialNoType	FutureSerial;
	///期货公司代码
	FutureIDType	FutureID;
	///资金帐号
	FutureAccountType	FutureAccount;
	///银行流水号
	TradeSerialNoType	BankSerial;
	///银行代码
	BankIDType	BankID;
	///银行分中心代码
	BankBrchIDType	BankBrchID;
	///银行账号
	BankAccountType	BankAccount;
	///证件号码
	CertCodeType	CertCode;
	///货币代码
	CurrencyCodeType	CurrencyCode;
	///发生金额
	MoneyType	TxAmount;
	///有效标志
	TransferValidFlagType	Flag;
};

///响应信息
struct RspInfoField
{
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///交易所
struct ExchangeField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///交易所名称
	ExchangeNameType	ExchangeName;
	///交易所属性
	ExchangePropertyType	ExchangeProperty;
};

///产品
struct ProductField
{
	///产品代码
	InstrumentIDType	ProductID;
	///产品名称
	ProductNameType	ProductName;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///产品类型
	ProductClassType	ProductClass;
	///合约数量乘数
	VolumeMultipleType	VolumeMultiple;
	///最小变动价位
	PriceType	PriceTick;
	///市价单最大下单量
	VolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	VolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	VolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	VolumeType	MinLimitOrderVolume;
	///持仓类型
	PositionTypeType	PositionType;
	///持仓日期类型
	PositionDateTypeType	PositionDateType;
	///平仓处理类型
	CloseDealTypeType	CloseDealType;
	///交易币种类型
	CurrencyIDType	TradeCurrencyID;
	///质押资金可用范围
	MortgageFundUseRangeType	MortgageFundUseRange;
	///交易所产品代码
	InstrumentIDType	ExchangeProductID;
	///合约基础商品乘数
	UnderlyingMultipleType	UnderlyingMultiple;
};

///合约
struct InstrumentField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///合约名称
	InstrumentNameType	InstrumentName;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///产品代码
	InstrumentIDType	ProductID;
	///产品类型
	ProductClassType	ProductClass;
	///交割年份
	YearType	DeliveryYear;
	///交割月
	MonthType	DeliveryMonth;
	///市价单最大下单量
	VolumeType	MaxMarketOrderVolume;
	///市价单最小下单量
	VolumeType	MinMarketOrderVolume;
	///限价单最大下单量
	VolumeType	MaxLimitOrderVolume;
	///限价单最小下单量
	VolumeType	MinLimitOrderVolume;
	///合约数量乘数
	VolumeMultipleType	VolumeMultiple;
	///最小变动价位
	PriceType	PriceTick;
	///创建日
	DateType	CreateDate;
	///上市日
	DateType	OpenDate;
	///到期日
	DateType	ExpireDate;
	///开始交割日
	DateType	StartDelivDate;
	///结束交割日
	DateType	EndDelivDate;
	///合约生命周期状态
	InstLifePhaseType	InstLifePhase;
	///当前是否交易
	BoolType	IsTrading;
	///持仓类型
	PositionTypeType	PositionType;
	///持仓日期类型
	PositionDateTypeType	PositionDateType;
	///多头保证金率
	RatioType	LongMarginRatio;
	///空头保证金率
	RatioType	ShortMarginRatio;
	///是否使用大额单边保证金算法
	MaxMarginSideAlgorithmType	MaxMarginSideAlgorithm;
	///基础商品代码
	InstrumentIDType	UnderlyingInstrID;
	///执行价
	PriceType	StrikePrice;
	///期权类型
	OptionsTypeType	OptionsType;
	///合约基础商品乘数
	UnderlyingMultipleType	UnderlyingMultiple;
	///组合类型
	CombinationTypeType	CombinationType;
};

///经纪公司
struct BrokerField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///经纪公司简称
	BrokerAbbrType	BrokerAbbr;
	///经纪公司名称
	BrokerNameType	BrokerName;
	///是否活跃
	BoolType	IsActive;
};

///交易所交易员
struct TraderField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///密码
	PasswordType	Password;
	///安装数量
	InstallCountType	InstallCount;
	///经纪公司代码
	BrokerIDType	BrokerID;
};

///投资者
struct InvestorField
{
	///投资者代码
	InvestorIDType	InvestorID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者分组代码
	InvestorIDType	InvestorGroupID;
	///投资者名称
	PartyNameType	InvestorName;
	///证件类型
	IdCardTypeType	IdentifiedCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///是否活跃
	BoolType	IsActive;
	///联系电话
	TelephoneType	Telephone;
	///通讯地址
	AddressType	Address;
	///开户日期
	DateType	OpenDate;
	///手机
	MobileType	Mobile;
	///手续费率模板代码
	InvestorIDType	CommModelID;
	///保证金率模板代码
	InvestorIDType	MarginModelID;
};

///交易编码
struct TradingCodeField
{
	///投资者代码
	InvestorIDType	InvestorID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///客户代码
	ClientIDType	ClientID;
	///是否活跃
	BoolType	IsActive;
	///交易编码类型
	ClientIDTypeType	ClientIDType;
};

///会员编码和经纪公司编码对照表
struct PartBrokerField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///是否活跃
	BoolType	IsActive;
};

///管理用户
struct SuperUserField
{
	///用户代码
	UserIDType	UserID;
	///用户名称
	UserNameType	UserName;
	///密码
	PasswordType	Password;
	///是否活跃
	BoolType	IsActive;
};

///管理用户功能权限
struct SuperUserFunctionField
{
	///用户代码
	UserIDType	UserID;
	///功能代码
	FunctionCodeType	FunctionCode;
};

///投资者组
struct InvestorGroupField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者分组代码
	InvestorIDType	InvestorGroupID;
	///投资者分组名称
	InvestorGroupNameType	InvestorGroupName;
};

///资金账户
struct TradingAccountField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者帐号
	AccountIDType	AccountID;
	///上次质押金额
	MoneyType	PreMortgage;
	///上次信用额度
	MoneyType	PreCredit;
	///上次存款额
	MoneyType	PreDeposit;
	///上次结算准备金
	MoneyType	PreBalance;
	///上次占用的保证金
	MoneyType	PreMargin;
	///利息基数
	MoneyType	InterestBase;
	///利息收入
	MoneyType	Interest;
	///入金金额
	MoneyType	Deposit;
	///出金金额
	MoneyType	Withdraw;
	///冻结的保证金
	MoneyType	FrozenMargin;
	///冻结的资金
	MoneyType	FrozenCash;
	///冻结的手续费
	MoneyType	FrozenCommission;
	///当前保证金总额
	MoneyType	CurrMargin;
	///资金差额
	MoneyType	CashIn;
	///手续费
	MoneyType	Commission;
	///平仓盈亏
	MoneyType	CloseProfit;
	///持仓盈亏
	MoneyType	PositionProfit;
	///期货结算准备金
	MoneyType	Balance;
	///可用资金
	MoneyType	Available;
	///可取资金
	MoneyType	WithdrawQuota;
	///基本准备金
	MoneyType	Reserve;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///信用额度
	MoneyType	Credit;
	///质押金额
	MoneyType	Mortgage;
	///交易所保证金
	MoneyType	ExchangeMargin;
	///投资者交割保证金
	MoneyType	DeliveryMargin;
	///交易所交割保证金
	MoneyType	ExchangeDeliveryMargin;
	///保底期货结算准备金
	MoneyType	ReserveBalance;
	///币种代码
	CurrencyIDType	CurrencyID;
	///上次货币质入金额
	MoneyType	PreFundMortgageIn;
	///上次货币质出金额
	MoneyType	PreFundMortgageOut;
	///货币质入金额
	MoneyType	FundMortgageIn;
	///货币质出金额
	MoneyType	FundMortgageOut;
	///货币质押余额
	MoneyType	FundMortgageAvailable;
	///可质押货币金额
	MoneyType	MortgageableFund;
	///特殊产品占用保证金
	MoneyType	SpecProductMargin;
	///特殊产品冻结保证金
	MoneyType	SpecProductFrozenMargin;
	///特殊产品手续费
	MoneyType	SpecProductCommission;
	///特殊产品冻结手续费
	MoneyType	SpecProductFrozenCommission;
	///特殊产品持仓盈亏
	MoneyType	SpecProductPositionProfit;
	///特殊产品平仓盈亏
	MoneyType	SpecProductCloseProfit;
	///根据持仓盈亏算法计算的特殊产品持仓盈亏
	MoneyType	SpecProductPositionProfitByAlg;
	///特殊产品交易所保证金
	MoneyType	SpecProductExchangeMargin;
};

///投资者持仓
struct InvestorPositionField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///持仓多空方向
	PosiDirectionType	PosiDirection;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///持仓日期
	PositionDateType	PositionDate;
	///上日持仓
	VolumeType	YdPosition;
	///今日持仓
	VolumeType	Position;
	///多头冻结
	VolumeType	LongFrozen;
	///空头冻结
	VolumeType	ShortFrozen;
	///开仓冻结金额
	MoneyType	LongFrozenAmount;
	///开仓冻结金额
	MoneyType	ShortFrozenAmount;
	///开仓量
	VolumeType	OpenVolume;
	///平仓量
	VolumeType	CloseVolume;
	///开仓金额
	MoneyType	OpenAmount;
	///平仓金额
	MoneyType	CloseAmount;
	///持仓成本
	MoneyType	PositionCost;
	///上次占用的保证金
	MoneyType	PreMargin;
	///占用的保证金
	MoneyType	UseMargin;
	///冻结的保证金
	MoneyType	FrozenMargin;
	///冻结的资金
	MoneyType	FrozenCash;
	///冻结的手续费
	MoneyType	FrozenCommission;
	///资金差额
	MoneyType	CashIn;
	///手续费
	MoneyType	Commission;
	///平仓盈亏
	MoneyType	CloseProfit;
	///持仓盈亏
	MoneyType	PositionProfit;
	///上次结算价
	PriceType	PreSettlementPrice;
	///本次结算价
	PriceType	SettlementPrice;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///开仓成本
	MoneyType	OpenCost;
	///交易所保证金
	MoneyType	ExchangeMargin;
	///组合成交形成的持仓
	VolumeType	CombPosition;
	///组合多头冻结
	VolumeType	CombLongFrozen;
	///组合空头冻结
	VolumeType	CombShortFrozen;
	///逐日盯市平仓盈亏
	MoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	MoneyType	CloseProfitByTrade;
	///今日持仓
	VolumeType	TodayPosition;
	///保证金率
	RatioType	MarginRateByMoney;
	///保证金率(按手数)
	RatioType	MarginRateByVolume;
	///执行冻结
	VolumeType	StrikeFrozen;
	///执行冻结金额
	MoneyType	StrikeFrozenAmount;
	///放弃执行冻结
	VolumeType	AbandonFrozen;
};

///合约保证金率
struct InstrumentMarginRateField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///多头保证金率
	RatioType	LongMarginRatioByMoney;
	///多头保证金费
	MoneyType	LongMarginRatioByVolume;
	///空头保证金率
	RatioType	ShortMarginRatioByMoney;
	///空头保证金费
	MoneyType	ShortMarginRatioByVolume;
	///是否相对交易所收取
	BoolType	IsRelative;
};

///合约手续费率
struct InstrumentCommissionRateField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///开仓手续费率
	RatioType	OpenRatioByMoney;
	///开仓手续费
	RatioType	OpenRatioByVolume;
	///平仓手续费率
	RatioType	CloseRatioByMoney;
	///平仓手续费
	RatioType	CloseRatioByVolume;
	///平今手续费率
	RatioType	CloseTodayRatioByMoney;
	///平今手续费
	RatioType	CloseTodayRatioByVolume;
};

///深度行情
struct DepthMarketDataField
{
	///交易日
	DateType	TradingDay;
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///最新价
	PriceType	LastPrice;
	///上次结算价
	PriceType	PreSettlementPrice;
	///昨收盘
	PriceType	PreClosePrice;
	///昨持仓量
	LargeVolumeType	PreOpenInterest;
	///今开盘
	PriceType	OpenPrice;
	///最高价
	PriceType	HighestPrice;
	///最低价
	PriceType	LowestPrice;
	///数量
	VolumeType	Volume;
	///成交金额
	MoneyType	Turnover;
	///持仓量
	LargeVolumeType	OpenInterest;
	///今收盘
	PriceType	ClosePrice;
	///本次结算价
	PriceType	SettlementPrice;
	///涨停板价
	PriceType	UpperLimitPrice;
	///跌停板价
	PriceType	LowerLimitPrice;
	///昨虚实度
	RatioType	PreDelta;
	///今虚实度
	RatioType	CurrDelta;
	///最后修改时间
	TimeType	UpdateTime;
	///最后修改毫秒
	MillisecType	UpdateMillisec;
	///申买价一
	PriceType	BidPrice1;
	///申买量一
	VolumeType	BidVolume1;
	///申卖价一
	PriceType	AskPrice1;
	///申卖量一
	VolumeType	AskVolume1;
	///申买价二
	PriceType	BidPrice2;
	///申买量二
	VolumeType	BidVolume2;
	///申卖价二
	PriceType	AskPrice2;
	///申卖量二
	VolumeType	AskVolume2;
	///申买价三
	PriceType	BidPrice3;
	///申买量三
	VolumeType	BidVolume3;
	///申卖价三
	PriceType	AskPrice3;
	///申卖量三
	VolumeType	AskVolume3;
	///申买价四
	PriceType	BidPrice4;
	///申买量四
	VolumeType	BidVolume4;
	///申卖价四
	PriceType	AskPrice4;
	///申卖量四
	VolumeType	AskVolume4;
	///申买价五
	PriceType	BidPrice5;
	///申买量五
	VolumeType	BidVolume5;
	///申卖价五
	PriceType	AskPrice5;
	///申卖量五
	VolumeType	AskVolume5;
	///当日均价
	PriceType	AveragePrice;
	///业务日期
	DateType	ActionDay;
};

///投资者合约交易权限
struct InstrumentTradingRightField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///交易权限
	TradingRightType	TradingRight;
};

///经纪公司用户
struct BrokerUserField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///用户名称
	UserNameType	UserName;
	///用户类型
	UserTypeType	UserType;
	///是否活跃
	BoolType	IsActive;
	///是否使用令牌
	BoolType	IsUsingOTP;
};

///经纪公司用户口令
struct BrokerUserPasswordField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///密码
	PasswordType	Password;
};

///经纪公司用户功能权限
struct BrokerUserFunctionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///经纪公司功能代码
	BrokerFunctionCodeType	BrokerFunctionCode;
};

///交易所交易员报盘机
struct TraderOfferField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///密码
	PasswordType	Password;
	///安装编号
	InstallIDType	InstallID;
	///本地报单编号
	OrderLocalIDType	OrderLocalID;
	///交易所交易员连接状态
	TraderConnectStatusType	TraderConnectStatus;
	///发出连接请求的日期
	DateType	ConnectRequestDate;
	///发出连接请求的时间
	TimeType	ConnectRequestTime;
	///上次报告日期
	DateType	LastReportDate;
	///上次报告时间
	TimeType	LastReportTime;
	///完成连接日期
	DateType	ConnectDate;
	///完成连接时间
	TimeType	ConnectTime;
	///启动日期
	DateType	StartDate;
	///启动时间
	TimeType	StartTime;
	///交易日
	DateType	TradingDay;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///本席位最大成交编号
	TradeIDType	MaxTradeID;
	///本席位最大报单备拷
	ReturnCodeType	MaxOrderMessageReference;
};

///投资者结算结果
struct SettlementInfoField
{
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///序号
	SequenceNoType	SequenceNo;
	///消息正文
	ContentType	Content;
};

///合约保证金率调整
struct InstrumentMarginRateAdjustField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///多头保证金率
	RatioType	LongMarginRatioByMoney;
	///多头保证金费
	MoneyType	LongMarginRatioByVolume;
	///空头保证金率
	RatioType	ShortMarginRatioByMoney;
	///空头保证金费
	MoneyType	ShortMarginRatioByVolume;
	///是否相对交易所收取
	BoolType	IsRelative;
};

///交易所保证金率
struct ExchangeMarginRateField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///多头保证金率
	RatioType	LongMarginRatioByMoney;
	///多头保证金费
	MoneyType	LongMarginRatioByVolume;
	///空头保证金率
	RatioType	ShortMarginRatioByMoney;
	///空头保证金费
	MoneyType	ShortMarginRatioByVolume;
};

///交易所保证金率调整
struct ExchangeMarginRateAdjustField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///跟随交易所投资者多头保证金率
	RatioType	LongMarginRatioByMoney;
	///跟随交易所投资者多头保证金费
	MoneyType	LongMarginRatioByVolume;
	///跟随交易所投资者空头保证金率
	RatioType	ShortMarginRatioByMoney;
	///跟随交易所投资者空头保证金费
	MoneyType	ShortMarginRatioByVolume;
	///交易所多头保证金率
	RatioType	ExchLongMarginRatioByMoney;
	///交易所多头保证金费
	MoneyType	ExchLongMarginRatioByVolume;
	///交易所空头保证金率
	RatioType	ExchShortMarginRatioByMoney;
	///交易所空头保证金费
	MoneyType	ExchShortMarginRatioByVolume;
	///不跟随交易所投资者多头保证金率
	RatioType	NoLongMarginRatioByMoney;
	///不跟随交易所投资者多头保证金费
	MoneyType	NoLongMarginRatioByVolume;
	///不跟随交易所投资者空头保证金率
	RatioType	NoShortMarginRatioByMoney;
	///不跟随交易所投资者空头保证金费
	MoneyType	NoShortMarginRatioByVolume;
};

///汇率
struct ExchangeRateField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///源币种
	CurrencyIDType	FromCurrencyID;
	///源币种单位数量
	CurrencyUnitType	FromCurrencyUnit;
	///目标币种
	CurrencyIDType	ToCurrencyID;
	///汇率
	ExchangeRateType	ExchangeRate;
};

///结算引用
struct SettlementRefField
{
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
};

///当前时间
struct CurrentTimeField
{
	///当前日期
	DateType	CurrDate;
	///当前时间
	TimeType	CurrTime;
	///当前时间（毫秒）
	MillisecType	CurrMillisec;
	///业务日期
	DateType	ActionDay;
};

///通讯阶段
struct CommPhaseField
{
	///交易日
	DateType	TradingDay;
	///通讯时段编号
	CommPhaseNoType	CommPhaseNo;
	///系统编号
	SystemIDType	SystemID;
};

///登录信息
struct LoginInfoField
{
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///登录日期
	DateType	LoginDate;
	///登录时间
	TimeType	LoginTime;
	///IP地址
	IPAddressType	IPAddress;
	///用户端产品信息
	ProductInfoType	UserProductInfo;
	///接口端产品信息
	ProductInfoType	InterfaceProductInfo;
	///协议信息
	ProtocolInfoType	ProtocolInfo;
	///系统名称
	SystemNameType	SystemName;
	///密码
	PasswordType	Password;
	///最大报单引用
	OrderRefType	MaxOrderRef;
	///上期所时间
	TimeType	SHFETime;
	///大商所时间
	TimeType	DCETime;
	///郑商所时间
	TimeType	CZCETime;
	///中金所时间
	TimeType	FFEXTime;
	///Mac地址
	MacAddressType	MacAddress;
	///动态密码
	PasswordType	OneTimePassword;
	///能源中心时间
	TimeType	INETime;
};

///登录信息
struct LogoutAllField
{
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///系统名称
	SystemNameType	SystemName;
};

///前置状态
struct FrontStatusField
{
	///前置编号
	FrontIDType	FrontID;
	///上次报告日期
	DateType	LastReportDate;
	///上次报告时间
	TimeType	LastReportTime;
	///是否活跃
	BoolType	IsActive;
};

///用户口令变更
struct UserPasswordUpdateField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///原来的口令
	PasswordType	OldPassword;
	///新的口令
	PasswordType	NewPassword;
};

///输入报单
struct InputOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///报单引用
	OrderRefType	OrderRef;
	///用户代码
	UserIDType	UserID;
	///报单价格条件
	OrderPriceTypeType	OrderPriceType;
	///买卖方向
	DirectionType	Direction;
	///组合开平标志
	CombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	CombHedgeFlagType	CombHedgeFlag;
	///价格
	PriceType	LimitPrice;
	///数量
	VolumeType	VolumeTotalOriginal;
	///有效期类型
	TimeConditionType	TimeCondition;
	///GTD日期
	DateType	GTDDate;
	///成交量类型
	VolumeConditionType	VolumeCondition;
	///最小成交量
	VolumeType	MinVolume;
	///触发条件
	ContingentConditionType	ContingentCondition;
	///止损价
	PriceType	StopPrice;
	///强平原因
	ForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	BoolType	IsAutoSuspend;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///请求编号
	RequestIDType	RequestID;
	///用户强评标志
	BoolType	UserForceClose;
	///互换单标志
	BoolType	IsSwapOrder;
};

///报单
struct OrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///报单引用
	OrderRefType	OrderRef;
	///用户代码
	UserIDType	UserID;
	///报单价格条件
	OrderPriceTypeType	OrderPriceType;
	///买卖方向
	DirectionType	Direction;
	///组合开平标志
	CombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	CombHedgeFlagType	CombHedgeFlag;
	///价格
	PriceType	LimitPrice;
	///数量
	VolumeType	VolumeTotalOriginal;
	///有效期类型
	TimeConditionType	TimeCondition;
	///GTD日期
	DateType	GTDDate;
	///成交量类型
	VolumeConditionType	VolumeCondition;
	///最小成交量
	VolumeType	MinVolume;
	///触发条件
	ContingentConditionType	ContingentCondition;
	///止损价
	PriceType	StopPrice;
	///强平原因
	ForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	BoolType	IsAutoSuspend;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///请求编号
	RequestIDType	RequestID;
	///本地报单编号
	OrderLocalIDType	OrderLocalID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///报单提交状态
	OrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	SequenceNoType	NotifySequence;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///报单编号
	OrderSysIDType	OrderSysID;
	///报单来源
	OrderSourceType	OrderSource;
	///报单状态
	OrderStatusType	OrderStatus;
	///报单类型
	OrderTypeType	OrderType;
	///今成交数量
	VolumeType	VolumeTraded;
	///剩余数量
	VolumeType	VolumeTotal;
	///报单日期
	DateType	InsertDate;
	///委托时间
	TimeType	InsertTime;
	///激活时间
	TimeType	ActiveTime;
	///挂起时间
	TimeType	SuspendTime;
	///最后修改时间
	TimeType	UpdateTime;
	///撤销时间
	TimeType	CancelTime;
	///最后修改交易所交易员代码
	TraderIDType	ActiveTraderID;
	///结算会员编号
	ParticipantIDType	ClearingPartID;
	///序号
	SequenceNoType	SequenceNo;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///用户端产品信息
	ProductInfoType	UserProductInfo;
	///状态信息
	ErrorMsgType	StatusMsg;
	///用户强评标志
	BoolType	UserForceClose;
	///操作用户代码
	UserIDType	ActiveUserID;
	///经纪公司报单编号
	SequenceNoType	BrokerOrderSeq;
	///相关报单
	OrderSysIDType	RelativeOrderSysID;
	///郑商所成交数量
	VolumeType	ZCETotalTradedVolume;
	///互换单标志
	BoolType	IsSwapOrder;
};

///交易所报单
struct ExchangeOrderField
{
	///报单价格条件
	OrderPriceTypeType	OrderPriceType;
	///买卖方向
	DirectionType	Direction;
	///组合开平标志
	CombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	CombHedgeFlagType	CombHedgeFlag;
	///价格
	PriceType	LimitPrice;
	///数量
	VolumeType	VolumeTotalOriginal;
	///有效期类型
	TimeConditionType	TimeCondition;
	///GTD日期
	DateType	GTDDate;
	///成交量类型
	VolumeConditionType	VolumeCondition;
	///最小成交量
	VolumeType	MinVolume;
	///触发条件
	ContingentConditionType	ContingentCondition;
	///止损价
	PriceType	StopPrice;
	///强平原因
	ForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	BoolType	IsAutoSuspend;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///请求编号
	RequestIDType	RequestID;
	///本地报单编号
	OrderLocalIDType	OrderLocalID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///报单提交状态
	OrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	SequenceNoType	NotifySequence;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///报单编号
	OrderSysIDType	OrderSysID;
	///报单来源
	OrderSourceType	OrderSource;
	///报单状态
	OrderStatusType	OrderStatus;
	///报单类型
	OrderTypeType	OrderType;
	///今成交数量
	VolumeType	VolumeTraded;
	///剩余数量
	VolumeType	VolumeTotal;
	///报单日期
	DateType	InsertDate;
	///委托时间
	TimeType	InsertTime;
	///激活时间
	TimeType	ActiveTime;
	///挂起时间
	TimeType	SuspendTime;
	///最后修改时间
	TimeType	UpdateTime;
	///撤销时间
	TimeType	CancelTime;
	///最后修改交易所交易员代码
	TraderIDType	ActiveTraderID;
	///结算会员编号
	ParticipantIDType	ClearingPartID;
	///序号
	SequenceNoType	SequenceNo;
};

///交易所报单插入失败
struct ExchangeOrderInsertErrorField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///本地报单编号
	OrderLocalIDType	OrderLocalID;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///输入报单操作
struct InputOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///报单操作引用
	OrderActionRefType	OrderActionRef;
	///报单引用
	OrderRefType	OrderRef;
	///请求编号
	RequestIDType	RequestID;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///报单编号
	OrderSysIDType	OrderSysID;
	///操作标志
	ActionFlagType	ActionFlag;
	///价格
	PriceType	LimitPrice;
	///数量变化
	VolumeType	VolumeChange;
	///用户代码
	UserIDType	UserID;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///报单操作
struct OrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///报单操作引用
	OrderActionRefType	OrderActionRef;
	///报单引用
	OrderRefType	OrderRef;
	///请求编号
	RequestIDType	RequestID;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///报单编号
	OrderSysIDType	OrderSysID;
	///操作标志
	ActionFlagType	ActionFlag;
	///价格
	PriceType	LimitPrice;
	///数量变化
	VolumeType	VolumeChange;
	///操作日期
	DateType	ActionDate;
	///操作时间
	TimeType	ActionTime;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///本地报单编号
	OrderLocalIDType	OrderLocalID;
	///操作本地编号
	OrderLocalIDType	ActionLocalID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///报单操作状态
	OrderActionStatusType	OrderActionStatus;
	///用户代码
	UserIDType	UserID;
	///状态信息
	ErrorMsgType	StatusMsg;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///交易所报单操作
struct ExchangeOrderActionField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///报单编号
	OrderSysIDType	OrderSysID;
	///操作标志
	ActionFlagType	ActionFlag;
	///价格
	PriceType	LimitPrice;
	///数量变化
	VolumeType	VolumeChange;
	///操作日期
	DateType	ActionDate;
	///操作时间
	TimeType	ActionTime;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///本地报单编号
	OrderLocalIDType	OrderLocalID;
	///操作本地编号
	OrderLocalIDType	ActionLocalID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///报单操作状态
	OrderActionStatusType	OrderActionStatus;
	///用户代码
	UserIDType	UserID;
};

///交易所报单操作失败
struct ExchangeOrderActionErrorField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///报单编号
	OrderSysIDType	OrderSysID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///本地报单编号
	OrderLocalIDType	OrderLocalID;
	///操作本地编号
	OrderLocalIDType	ActionLocalID;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///交易所成交
struct ExchangeTradeField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///成交编号
	TradeIDType	TradeID;
	///买卖方向
	DirectionType	Direction;
	///报单编号
	OrderSysIDType	OrderSysID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///交易角色
	TradingRoleType	TradingRole;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///开平标志
	OffsetFlagType	OffsetFlag;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///价格
	PriceType	Price;
	///数量
	VolumeType	Volume;
	///成交时期
	DateType	TradeDate;
	///成交时间
	TimeType	TradeTime;
	///成交类型
	TradeTypeType	TradeType;
	///成交价来源
	PriceSourceType	PriceSource;
	///交易所交易员代码
	TraderIDType	TraderID;
	///本地报单编号
	OrderLocalIDType	OrderLocalID;
	///结算会员编号
	ParticipantIDType	ClearingPartID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///序号
	SequenceNoType	SequenceNo;
	///成交来源
	TradeSourceType	TradeSource;
};

///成交
struct TradeField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///报单引用
	OrderRefType	OrderRef;
	///用户代码
	UserIDType	UserID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///成交编号
	TradeIDType	TradeID;
	///买卖方向
	DirectionType	Direction;
	///报单编号
	OrderSysIDType	OrderSysID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///交易角色
	TradingRoleType	TradingRole;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///开平标志
	OffsetFlagType	OffsetFlag;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///价格
	PriceType	Price;
	///数量
	VolumeType	Volume;
	///成交时期
	DateType	TradeDate;
	///成交时间
	TimeType	TradeTime;
	///成交类型
	TradeTypeType	TradeType;
	///成交价来源
	PriceSourceType	PriceSource;
	///交易所交易员代码
	TraderIDType	TraderID;
	///本地报单编号
	OrderLocalIDType	OrderLocalID;
	///结算会员编号
	ParticipantIDType	ClearingPartID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///序号
	SequenceNoType	SequenceNo;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///经纪公司报单编号
	SequenceNoType	BrokerOrderSeq;
	///成交来源
	TradeSourceType	TradeSource;
};

///用户会话
struct UserSessionField
{
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///登录日期
	DateType	LoginDate;
	///登录时间
	TimeType	LoginTime;
	///IP地址
	IPAddressType	IPAddress;
	///用户端产品信息
	ProductInfoType	UserProductInfo;
	///接口端产品信息
	ProductInfoType	InterfaceProductInfo;
	///协议信息
	ProtocolInfoType	ProtocolInfo;
	///Mac地址
	MacAddressType	MacAddress;
};

///查询最大报单数量
struct QueryMaxOrderVolumeField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///买卖方向
	DirectionType	Direction;
	///开平标志
	OffsetFlagType	OffsetFlag;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///最大允许报单数量
	VolumeType	MaxVolume;
};

///投资者结算结果确认信息
struct SettlementInfoConfirmField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///确认日期
	DateType	ConfirmDate;
	///确认时间
	TimeType	ConfirmTime;
};

///出入金同步
struct SyncDepositField
{
	///出入金流水号
	DepositSeqNoType	DepositSeqNo;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///入金金额
	MoneyType	Deposit;
	///是否强制进行
	BoolType	IsForce;
	///币种代码
	CurrencyIDType	CurrencyID;
};

///货币质押同步
struct SyncFundMortgageField
{
	///货币质押流水号
	DepositSeqNoType	MortgageSeqNo;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///源币种
	CurrencyIDType	FromCurrencyID;
	///质押金额
	MoneyType	MortgageAmount;
	///目标币种
	CurrencyIDType	ToCurrencyID;
};

///经纪公司同步
struct BrokerSyncField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
};

///正在同步中的投资者
struct SyncingInvestorField
{
	///投资者代码
	InvestorIDType	InvestorID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者分组代码
	InvestorIDType	InvestorGroupID;
	///投资者名称
	PartyNameType	InvestorName;
	///证件类型
	IdCardTypeType	IdentifiedCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///是否活跃
	BoolType	IsActive;
	///联系电话
	TelephoneType	Telephone;
	///通讯地址
	AddressType	Address;
	///开户日期
	DateType	OpenDate;
	///手机
	MobileType	Mobile;
	///手续费率模板代码
	InvestorIDType	CommModelID;
	///保证金率模板代码
	InvestorIDType	MarginModelID;
};

///正在同步中的交易代码
struct SyncingTradingCodeField
{
	///投资者代码
	InvestorIDType	InvestorID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///客户代码
	ClientIDType	ClientID;
	///是否活跃
	BoolType	IsActive;
	///交易编码类型
	ClientIDTypeType	ClientIDType;
};

///正在同步中的投资者分组
struct SyncingInvestorGroupField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者分组代码
	InvestorIDType	InvestorGroupID;
	///投资者分组名称
	InvestorGroupNameType	InvestorGroupName;
};

///正在同步中的交易账号
struct SyncingTradingAccountField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者帐号
	AccountIDType	AccountID;
	///上次质押金额
	MoneyType	PreMortgage;
	///上次信用额度
	MoneyType	PreCredit;
	///上次存款额
	MoneyType	PreDeposit;
	///上次结算准备金
	MoneyType	PreBalance;
	///上次占用的保证金
	MoneyType	PreMargin;
	///利息基数
	MoneyType	InterestBase;
	///利息收入
	MoneyType	Interest;
	///入金金额
	MoneyType	Deposit;
	///出金金额
	MoneyType	Withdraw;
	///冻结的保证金
	MoneyType	FrozenMargin;
	///冻结的资金
	MoneyType	FrozenCash;
	///冻结的手续费
	MoneyType	FrozenCommission;
	///当前保证金总额
	MoneyType	CurrMargin;
	///资金差额
	MoneyType	CashIn;
	///手续费
	MoneyType	Commission;
	///平仓盈亏
	MoneyType	CloseProfit;
	///持仓盈亏
	MoneyType	PositionProfit;
	///期货结算准备金
	MoneyType	Balance;
	///可用资金
	MoneyType	Available;
	///可取资金
	MoneyType	WithdrawQuota;
	///基本准备金
	MoneyType	Reserve;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///信用额度
	MoneyType	Credit;
	///质押金额
	MoneyType	Mortgage;
	///交易所保证金
	MoneyType	ExchangeMargin;
	///投资者交割保证金
	MoneyType	DeliveryMargin;
	///交易所交割保证金
	MoneyType	ExchangeDeliveryMargin;
	///保底期货结算准备金
	MoneyType	ReserveBalance;
	///币种代码
	CurrencyIDType	CurrencyID;
	///上次货币质入金额
	MoneyType	PreFundMortgageIn;
	///上次货币质出金额
	MoneyType	PreFundMortgageOut;
	///货币质入金额
	MoneyType	FundMortgageIn;
	///货币质出金额
	MoneyType	FundMortgageOut;
	///货币质押余额
	MoneyType	FundMortgageAvailable;
	///可质押货币金额
	MoneyType	MortgageableFund;
	///特殊产品占用保证金
	MoneyType	SpecProductMargin;
	///特殊产品冻结保证金
	MoneyType	SpecProductFrozenMargin;
	///特殊产品手续费
	MoneyType	SpecProductCommission;
	///特殊产品冻结手续费
	MoneyType	SpecProductFrozenCommission;
	///特殊产品持仓盈亏
	MoneyType	SpecProductPositionProfit;
	///特殊产品平仓盈亏
	MoneyType	SpecProductCloseProfit;
	///根据持仓盈亏算法计算的特殊产品持仓盈亏
	MoneyType	SpecProductPositionProfitByAlg;
	///特殊产品交易所保证金
	MoneyType	SpecProductExchangeMargin;
};

///正在同步中的投资者持仓
struct SyncingInvestorPositionField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///持仓多空方向
	PosiDirectionType	PosiDirection;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///持仓日期
	PositionDateType	PositionDate;
	///上日持仓
	VolumeType	YdPosition;
	///今日持仓
	VolumeType	Position;
	///多头冻结
	VolumeType	LongFrozen;
	///空头冻结
	VolumeType	ShortFrozen;
	///开仓冻结金额
	MoneyType	LongFrozenAmount;
	///开仓冻结金额
	MoneyType	ShortFrozenAmount;
	///开仓量
	VolumeType	OpenVolume;
	///平仓量
	VolumeType	CloseVolume;
	///开仓金额
	MoneyType	OpenAmount;
	///平仓金额
	MoneyType	CloseAmount;
	///持仓成本
	MoneyType	PositionCost;
	///上次占用的保证金
	MoneyType	PreMargin;
	///占用的保证金
	MoneyType	UseMargin;
	///冻结的保证金
	MoneyType	FrozenMargin;
	///冻结的资金
	MoneyType	FrozenCash;
	///冻结的手续费
	MoneyType	FrozenCommission;
	///资金差额
	MoneyType	CashIn;
	///手续费
	MoneyType	Commission;
	///平仓盈亏
	MoneyType	CloseProfit;
	///持仓盈亏
	MoneyType	PositionProfit;
	///上次结算价
	PriceType	PreSettlementPrice;
	///本次结算价
	PriceType	SettlementPrice;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///开仓成本
	MoneyType	OpenCost;
	///交易所保证金
	MoneyType	ExchangeMargin;
	///组合成交形成的持仓
	VolumeType	CombPosition;
	///组合多头冻结
	VolumeType	CombLongFrozen;
	///组合空头冻结
	VolumeType	CombShortFrozen;
	///逐日盯市平仓盈亏
	MoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	MoneyType	CloseProfitByTrade;
	///今日持仓
	VolumeType	TodayPosition;
	///保证金率
	RatioType	MarginRateByMoney;
	///保证金率(按手数)
	RatioType	MarginRateByVolume;
	///执行冻结
	VolumeType	StrikeFrozen;
	///执行冻结金额
	MoneyType	StrikeFrozenAmount;
	///放弃执行冻结
	VolumeType	AbandonFrozen;
};

///正在同步中的合约保证金率
struct SyncingInstrumentMarginRateField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///多头保证金率
	RatioType	LongMarginRatioByMoney;
	///多头保证金费
	MoneyType	LongMarginRatioByVolume;
	///空头保证金率
	RatioType	ShortMarginRatioByMoney;
	///空头保证金费
	MoneyType	ShortMarginRatioByVolume;
	///是否相对交易所收取
	BoolType	IsRelative;
};

///正在同步中的合约手续费率
struct SyncingInstrumentCommissionRateField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///开仓手续费率
	RatioType	OpenRatioByMoney;
	///开仓手续费
	RatioType	OpenRatioByVolume;
	///平仓手续费率
	RatioType	CloseRatioByMoney;
	///平仓手续费
	RatioType	CloseRatioByVolume;
	///平今手续费率
	RatioType	CloseTodayRatioByMoney;
	///平今手续费
	RatioType	CloseTodayRatioByVolume;
};

///正在同步中的合约交易权限
struct SyncingInstrumentTradingRightField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///交易权限
	TradingRightType	TradingRight;
};

///查询报单
struct QryOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///报单编号
	OrderSysIDType	OrderSysID;
	///开始时间
	TimeType	InsertTimeStart;
	///结束时间
	TimeType	InsertTimeEnd;
};

///查询成交
struct QryTradeField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///成交编号
	TradeIDType	TradeID;
	///开始时间
	TimeType	TradeTimeStart;
	///结束时间
	TimeType	TradeTimeEnd;
};

///查询投资者持仓
struct QryInvestorPositionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///查询资金账户
struct QryTradingAccountField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///币种代码
	CurrencyIDType	CurrencyID;
};

///查询投资者
struct QryInvestorField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
};

///查询交易编码
struct QryTradingCodeField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///客户代码
	ClientIDType	ClientID;
	///交易编码类型
	ClientIDTypeType	ClientIDType;
};

///查询投资者组
struct QryInvestorGroupField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
};

///查询合约保证金率
struct QryInstrumentMarginRateField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
};

///查询手续费率
struct QryInstrumentCommissionRateField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///查询合约交易权限
struct QryInstrumentTradingRightField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///查询经纪公司
struct QryBrokerField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
};

///查询交易员
struct QryTraderField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///交易所交易员代码
	TraderIDType	TraderID;
};

///查询管理用户功能权限
struct QrySuperUserFunctionField
{
	///用户代码
	UserIDType	UserID;
};

///查询用户会话
struct QryUserSessionField
{
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
};

///查询经纪公司会员代码
struct QryPartBrokerField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///会员代码
	ParticipantIDType	ParticipantID;
};

///查询前置状态
struct QryFrontStatusField
{
	///前置编号
	FrontIDType	FrontID;
};

///查询交易所报单
struct QryExchangeOrderField
{
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///交易所交易员代码
	TraderIDType	TraderID;
};

///查询报单操作
struct QryOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///查询交易所报单操作
struct QryExchangeOrderActionField
{
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///交易所交易员代码
	TraderIDType	TraderID;
};

///查询管理用户
struct QrySuperUserField
{
	///用户代码
	UserIDType	UserID;
};

///查询交易所
struct QryExchangeField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///查询产品
struct QryProductField
{
	///产品代码
	InstrumentIDType	ProductID;
	///产品类型
	ProductClassType	ProductClass;
};

///查询合约
struct QryInstrumentField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///产品代码
	InstrumentIDType	ProductID;
};

///查询行情
struct QryDepthMarketDataField
{
	///合约代码
	InstrumentIDType	InstrumentID;
};

///查询经纪公司用户
struct QryBrokerUserField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
};

///查询经纪公司用户权限
struct QryBrokerUserFunctionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
};

///查询交易员报盘机
struct QryTraderOfferField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///交易所交易员代码
	TraderIDType	TraderID;
};

///查询出入金流水
struct QrySyncDepositField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///出入金流水号
	DepositSeqNoType	DepositSeqNo;
};

///查询投资者结算结果
struct QrySettlementInfoField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///交易日
	DateType	TradingDay;
};

///查询交易所保证金率
struct QryExchangeMarginRateField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
};

///查询交易所调整保证金率
struct QryExchangeMarginRateAdjustField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
};

///查询汇率
struct QryExchangeRateField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///源币种
	CurrencyIDType	FromCurrencyID;
	///目标币种
	CurrencyIDType	ToCurrencyID;
};

///查询货币质押流水
struct QrySyncFundMortgageField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///货币质押流水号
	DepositSeqNoType	MortgageSeqNo;
};

///查询报单
struct QryHisOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///报单编号
	OrderSysIDType	OrderSysID;
	///开始时间
	TimeType	InsertTimeStart;
	///结束时间
	TimeType	InsertTimeEnd;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
};

///当前期权合约最小保证金
struct OptionInstrMiniMarginField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///单位（手）期权合约最小保证金
	MoneyType	MinMargin;
	///取值方式
	ValueMethodType	ValueMethod;
	///是否跟随交易所收取
	BoolType	IsRelative;
};

///当前期权合约保证金调整系数
struct OptionInstrMarginAdjustField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///投机空头保证金调整系数
	RatioType	SShortMarginRatioByMoney;
	///投机空头保证金调整系数
	MoneyType	SShortMarginRatioByVolume;
	///保值空头保证金调整系数
	RatioType	HShortMarginRatioByMoney;
	///保值空头保证金调整系数
	MoneyType	HShortMarginRatioByVolume;
	///套利空头保证金调整系数
	RatioType	AShortMarginRatioByMoney;
	///套利空头保证金调整系数
	MoneyType	AShortMarginRatioByVolume;
	///是否跟随交易所收取
	BoolType	IsRelative;
};

///当前期权合约手续费的详细内容
struct OptionInstrCommRateField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///开仓手续费率
	RatioType	OpenRatioByMoney;
	///开仓手续费
	RatioType	OpenRatioByVolume;
	///平仓手续费率
	RatioType	CloseRatioByMoney;
	///平仓手续费
	RatioType	CloseRatioByVolume;
	///平今手续费率
	RatioType	CloseTodayRatioByMoney;
	///平今手续费
	RatioType	CloseTodayRatioByVolume;
	///执行手续费率
	RatioType	StrikeRatioByMoney;
	///执行手续费
	RatioType	StrikeRatioByVolume;
};

///期权交易成本
struct OptionInstrTradeCostField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///期权合约保证金不变部分
	MoneyType	FixedMargin;
	///期权合约最小保证金
	MoneyType	MiniMargin;
	///期权合约权利金
	MoneyType	Royalty;
	///交易所期权合约保证金不变部分
	MoneyType	ExchFixedMargin;
	///交易所期权合约最小保证金
	MoneyType	ExchMiniMargin;
};

///期权交易成本查询
struct QryOptionInstrTradeCostField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///期权合约报价
	PriceType	InputPrice;
	///标的价格,填0则用昨结算价
	PriceType	UnderlyingPrice;
};

///期权手续费率查询
struct QryOptionInstrCommRateField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///股指现货指数
struct IndexPriceField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///指数现货收盘价
	PriceType	ClosePrice;
};

///输入的执行宣告
struct InputExecOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///执行宣告引用
	OrderRefType	ExecOrderRef;
	///用户代码
	UserIDType	UserID;
	///数量
	VolumeType	Volume;
	///请求编号
	RequestIDType	RequestID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///开平标志
	OffsetFlagType	OffsetFlag;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///执行类型
	ActionTypeType	ActionType;
	///保留头寸申请的持仓方向
	PosiDirectionType	PosiDirection;
	///期权行权后是否保留期货头寸的标记
	ExecOrderPositionFlagType	ReservePositionFlag;
	///期权行权后生成的头寸是否自动平仓
	ExecOrderCloseFlagType	CloseFlag;
};

///输入执行宣告操作
struct InputExecOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///执行宣告操作引用
	OrderActionRefType	ExecOrderActionRef;
	///执行宣告引用
	OrderRefType	ExecOrderRef;
	///请求编号
	RequestIDType	RequestID;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///执行宣告操作编号
	ExecOrderSysIDType	ExecOrderSysID;
	///操作标志
	ActionFlagType	ActionFlag;
	///用户代码
	UserIDType	UserID;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///执行宣告
struct ExecOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///执行宣告引用
	OrderRefType	ExecOrderRef;
	///用户代码
	UserIDType	UserID;
	///数量
	VolumeType	Volume;
	///请求编号
	RequestIDType	RequestID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///开平标志
	OffsetFlagType	OffsetFlag;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///执行类型
	ActionTypeType	ActionType;
	///保留头寸申请的持仓方向
	PosiDirectionType	PosiDirection;
	///期权行权后是否保留期货头寸的标记
	ExecOrderPositionFlagType	ReservePositionFlag;
	///期权行权后生成的头寸是否自动平仓
	ExecOrderCloseFlagType	CloseFlag;
	///本地执行宣告编号
	OrderLocalIDType	ExecOrderLocalID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///执行宣告提交状态
	OrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	SequenceNoType	NotifySequence;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///执行宣告编号
	ExecOrderSysIDType	ExecOrderSysID;
	///报单日期
	DateType	InsertDate;
	///插入时间
	TimeType	InsertTime;
	///撤销时间
	TimeType	CancelTime;
	///执行结果
	ExecResultType	ExecResult;
	///结算会员编号
	ParticipantIDType	ClearingPartID;
	///序号
	SequenceNoType	SequenceNo;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///用户端产品信息
	ProductInfoType	UserProductInfo;
	///状态信息
	ErrorMsgType	StatusMsg;
	///操作用户代码
	UserIDType	ActiveUserID;
	///经纪公司报单编号
	SequenceNoType	BrokerExecOrderSeq;
};

///执行宣告操作
struct ExecOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///执行宣告操作引用
	OrderActionRefType	ExecOrderActionRef;
	///执行宣告引用
	OrderRefType	ExecOrderRef;
	///请求编号
	RequestIDType	RequestID;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///执行宣告操作编号
	ExecOrderSysIDType	ExecOrderSysID;
	///操作标志
	ActionFlagType	ActionFlag;
	///操作日期
	DateType	ActionDate;
	///操作时间
	TimeType	ActionTime;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///本地执行宣告编号
	OrderLocalIDType	ExecOrderLocalID;
	///操作本地编号
	OrderLocalIDType	ActionLocalID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///报单操作状态
	OrderActionStatusType	OrderActionStatus;
	///用户代码
	UserIDType	UserID;
	///执行类型
	ActionTypeType	ActionType;
	///状态信息
	ErrorMsgType	StatusMsg;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///执行宣告查询
struct QryExecOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///执行宣告编号
	ExecOrderSysIDType	ExecOrderSysID;
	///开始时间
	TimeType	InsertTimeStart;
	///结束时间
	TimeType	InsertTimeEnd;
};

///交易所执行宣告信息
struct ExchangeExecOrderField
{
	///数量
	VolumeType	Volume;
	///请求编号
	RequestIDType	RequestID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///开平标志
	OffsetFlagType	OffsetFlag;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///执行类型
	ActionTypeType	ActionType;
	///保留头寸申请的持仓方向
	PosiDirectionType	PosiDirection;
	///期权行权后是否保留期货头寸的标记
	ExecOrderPositionFlagType	ReservePositionFlag;
	///期权行权后生成的头寸是否自动平仓
	ExecOrderCloseFlagType	CloseFlag;
	///本地执行宣告编号
	OrderLocalIDType	ExecOrderLocalID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///执行宣告提交状态
	OrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	SequenceNoType	NotifySequence;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///执行宣告编号
	ExecOrderSysIDType	ExecOrderSysID;
	///报单日期
	DateType	InsertDate;
	///插入时间
	TimeType	InsertTime;
	///撤销时间
	TimeType	CancelTime;
	///执行结果
	ExecResultType	ExecResult;
	///结算会员编号
	ParticipantIDType	ClearingPartID;
	///序号
	SequenceNoType	SequenceNo;
};

///交易所执行宣告查询
struct QryExchangeExecOrderField
{
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///交易所交易员代码
	TraderIDType	TraderID;
};

///执行宣告操作查询
struct QryExecOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///交易所执行宣告操作
struct ExchangeExecOrderActionField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///执行宣告操作编号
	ExecOrderSysIDType	ExecOrderSysID;
	///操作标志
	ActionFlagType	ActionFlag;
	///操作日期
	DateType	ActionDate;
	///操作时间
	TimeType	ActionTime;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///本地执行宣告编号
	OrderLocalIDType	ExecOrderLocalID;
	///操作本地编号
	OrderLocalIDType	ActionLocalID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///报单操作状态
	OrderActionStatusType	OrderActionStatus;
	///用户代码
	UserIDType	UserID;
	///执行类型
	ActionTypeType	ActionType;
};

///交易所执行宣告操作查询
struct QryExchangeExecOrderActionField
{
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///交易所交易员代码
	TraderIDType	TraderID;
};

///错误执行宣告
struct ErrExecOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///执行宣告引用
	OrderRefType	ExecOrderRef;
	///用户代码
	UserIDType	UserID;
	///数量
	VolumeType	Volume;
	///请求编号
	RequestIDType	RequestID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///开平标志
	OffsetFlagType	OffsetFlag;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///执行类型
	ActionTypeType	ActionType;
	///保留头寸申请的持仓方向
	PosiDirectionType	PosiDirection;
	///期权行权后是否保留期货头寸的标记
	ExecOrderPositionFlagType	ReservePositionFlag;
	///期权行权后生成的头寸是否自动平仓
	ExecOrderCloseFlagType	CloseFlag;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///查询错误执行宣告
struct QryErrExecOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
};

///错误执行宣告操作
struct ErrExecOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///执行宣告操作引用
	OrderActionRefType	ExecOrderActionRef;
	///执行宣告引用
	OrderRefType	ExecOrderRef;
	///请求编号
	RequestIDType	RequestID;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///执行宣告操作编号
	ExecOrderSysIDType	ExecOrderSysID;
	///操作标志
	ActionFlagType	ActionFlag;
	///用户代码
	UserIDType	UserID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///查询错误执行宣告操作
struct QryErrExecOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
};

///投资者期权合约交易权限
struct OptionInstrTradingRightField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///买卖方向
	DirectionType	Direction;
	///交易权限
	TradingRightType	TradingRight;
};

///查询期权合约交易权限
struct QryOptionInstrTradingRightField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///买卖方向
	DirectionType	Direction;
};

///输入的询价
struct InputForQuoteField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///询价引用
	OrderRefType	ForQuoteRef;
	///用户代码
	UserIDType	UserID;
};

///询价
struct ForQuoteField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///询价引用
	OrderRefType	ForQuoteRef;
	///用户代码
	UserIDType	UserID;
	///本地询价编号
	OrderLocalIDType	ForQuoteLocalID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///报单日期
	DateType	InsertDate;
	///插入时间
	TimeType	InsertTime;
	///询价状态
	ForQuoteStatusType	ForQuoteStatus;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///状态信息
	ErrorMsgType	StatusMsg;
	///操作用户代码
	UserIDType	ActiveUserID;
	///经纪公司询价编号
	SequenceNoType	BrokerForQutoSeq;
};

///询价查询
struct QryForQuoteField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///开始时间
	TimeType	InsertTimeStart;
	///结束时间
	TimeType	InsertTimeEnd;
};

///交易所询价信息
struct ExchangeForQuoteField
{
	///本地询价编号
	OrderLocalIDType	ForQuoteLocalID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///报单日期
	DateType	InsertDate;
	///插入时间
	TimeType	InsertTime;
	///询价状态
	ForQuoteStatusType	ForQuoteStatus;
};

///交易所询价查询
struct QryExchangeForQuoteField
{
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///交易所交易员代码
	TraderIDType	TraderID;
};

///输入的报价
struct InputQuoteField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///报价引用
	OrderRefType	QuoteRef;
	///用户代码
	UserIDType	UserID;
	///卖价格
	PriceType	AskPrice;
	///买价格
	PriceType	BidPrice;
	///卖数量
	VolumeType	AskVolume;
	///买数量
	VolumeType	BidVolume;
	///请求编号
	RequestIDType	RequestID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///卖开平标志
	OffsetFlagType	AskOffsetFlag;
	///买开平标志
	OffsetFlagType	BidOffsetFlag;
	///卖投机套保标志
	HedgeFlagType	AskHedgeFlag;
	///买投机套保标志
	HedgeFlagType	BidHedgeFlag;
	///衍生卖报单引用
	OrderRefType	AskOrderRef;
	///衍生买报单引用
	OrderRefType	BidOrderRef;
	///应价编号
	OrderSysIDType	ForQuoteSysID;
};

///输入报价操作
struct InputQuoteActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///报价操作引用
	OrderActionRefType	QuoteActionRef;
	///报价引用
	OrderRefType	QuoteRef;
	///请求编号
	RequestIDType	RequestID;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///报价操作编号
	OrderSysIDType	QuoteSysID;
	///操作标志
	ActionFlagType	ActionFlag;
	///用户代码
	UserIDType	UserID;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///报价
struct QuoteField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///报价引用
	OrderRefType	QuoteRef;
	///用户代码
	UserIDType	UserID;
	///卖价格
	PriceType	AskPrice;
	///买价格
	PriceType	BidPrice;
	///卖数量
	VolumeType	AskVolume;
	///买数量
	VolumeType	BidVolume;
	///请求编号
	RequestIDType	RequestID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///卖开平标志
	OffsetFlagType	AskOffsetFlag;
	///买开平标志
	OffsetFlagType	BidOffsetFlag;
	///卖投机套保标志
	HedgeFlagType	AskHedgeFlag;
	///买投机套保标志
	HedgeFlagType	BidHedgeFlag;
	///本地报价编号
	OrderLocalIDType	QuoteLocalID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///报价提示序号
	SequenceNoType	NotifySequence;
	///报价提交状态
	OrderSubmitStatusType	OrderSubmitStatus;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///报价编号
	OrderSysIDType	QuoteSysID;
	///报单日期
	DateType	InsertDate;
	///插入时间
	TimeType	InsertTime;
	///撤销时间
	TimeType	CancelTime;
	///报价状态
	OrderStatusType	QuoteStatus;
	///结算会员编号
	ParticipantIDType	ClearingPartID;
	///序号
	SequenceNoType	SequenceNo;
	///卖方报单编号
	OrderSysIDType	AskOrderSysID;
	///买方报单编号
	OrderSysIDType	BidOrderSysID;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///用户端产品信息
	ProductInfoType	UserProductInfo;
	///状态信息
	ErrorMsgType	StatusMsg;
	///操作用户代码
	UserIDType	ActiveUserID;
	///经纪公司报价编号
	SequenceNoType	BrokerQuoteSeq;
	///衍生卖报单引用
	OrderRefType	AskOrderRef;
	///衍生买报单引用
	OrderRefType	BidOrderRef;
	///应价编号
	OrderSysIDType	ForQuoteSysID;
};

///报价操作
struct QuoteActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///报价操作引用
	OrderActionRefType	QuoteActionRef;
	///报价引用
	OrderRefType	QuoteRef;
	///请求编号
	RequestIDType	RequestID;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///报价操作编号
	OrderSysIDType	QuoteSysID;
	///操作标志
	ActionFlagType	ActionFlag;
	///操作日期
	DateType	ActionDate;
	///操作时间
	TimeType	ActionTime;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///本地报价编号
	OrderLocalIDType	QuoteLocalID;
	///操作本地编号
	OrderLocalIDType	ActionLocalID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///报单操作状态
	OrderActionStatusType	OrderActionStatus;
	///用户代码
	UserIDType	UserID;
	///状态信息
	ErrorMsgType	StatusMsg;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///报价查询
struct QryQuoteField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///报价编号
	OrderSysIDType	QuoteSysID;
	///开始时间
	TimeType	InsertTimeStart;
	///结束时间
	TimeType	InsertTimeEnd;
};

///交易所报价信息
struct ExchangeQuoteField
{
	///卖价格
	PriceType	AskPrice;
	///买价格
	PriceType	BidPrice;
	///卖数量
	VolumeType	AskVolume;
	///买数量
	VolumeType	BidVolume;
	///请求编号
	RequestIDType	RequestID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///卖开平标志
	OffsetFlagType	AskOffsetFlag;
	///买开平标志
	OffsetFlagType	BidOffsetFlag;
	///卖投机套保标志
	HedgeFlagType	AskHedgeFlag;
	///买投机套保标志
	HedgeFlagType	BidHedgeFlag;
	///本地报价编号
	OrderLocalIDType	QuoteLocalID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///报价提示序号
	SequenceNoType	NotifySequence;
	///报价提交状态
	OrderSubmitStatusType	OrderSubmitStatus;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///报价编号
	OrderSysIDType	QuoteSysID;
	///报单日期
	DateType	InsertDate;
	///插入时间
	TimeType	InsertTime;
	///撤销时间
	TimeType	CancelTime;
	///报价状态
	OrderStatusType	QuoteStatus;
	///结算会员编号
	ParticipantIDType	ClearingPartID;
	///序号
	SequenceNoType	SequenceNo;
	///卖方报单编号
	OrderSysIDType	AskOrderSysID;
	///买方报单编号
	OrderSysIDType	BidOrderSysID;
	///应价编号
	OrderSysIDType	ForQuoteSysID;
};

///交易所报价查询
struct QryExchangeQuoteField
{
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///交易所交易员代码
	TraderIDType	TraderID;
};

///报价操作查询
struct QryQuoteActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///交易所报价操作
struct ExchangeQuoteActionField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///报价操作编号
	OrderSysIDType	QuoteSysID;
	///操作标志
	ActionFlagType	ActionFlag;
	///操作日期
	DateType	ActionDate;
	///操作时间
	TimeType	ActionTime;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///本地报价编号
	OrderLocalIDType	QuoteLocalID;
	///操作本地编号
	OrderLocalIDType	ActionLocalID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///报单操作状态
	OrderActionStatusType	OrderActionStatus;
	///用户代码
	UserIDType	UserID;
};

///交易所报价操作查询
struct QryExchangeQuoteActionField
{
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///交易所交易员代码
	TraderIDType	TraderID;
};

///期权合约delta值
struct OptionInstrDeltaField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///Delta值
	RatioType	Delta;
};

///发给做市商的询价请求
struct ForQuoteRspField
{
	///交易日
	DateType	TradingDay;
	///合约代码
	InstrumentIDType	InstrumentID;
	///询价编号
	OrderSysIDType	ForQuoteSysID;
	///询价时间
	TimeType	ForQuoteTime;
	///业务日期
	DateType	ActionDay;
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///当前期权合约执行偏移值的详细内容
struct StrikeOffsetField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///执行偏移值
	MoneyType	Offset;
};

///期权执行偏移值查询
struct QryStrikeOffsetField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///输入批量报单操作
struct InputBatchOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///报单操作引用
	OrderActionRefType	OrderActionRef;
	///请求编号
	RequestIDType	RequestID;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///用户代码
	UserIDType	UserID;
};

///批量报单操作
struct BatchOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///报单操作引用
	OrderActionRefType	OrderActionRef;
	///请求编号
	RequestIDType	RequestID;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///操作日期
	DateType	ActionDate;
	///操作时间
	TimeType	ActionTime;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///操作本地编号
	OrderLocalIDType	ActionLocalID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///报单操作状态
	OrderActionStatusType	OrderActionStatus;
	///用户代码
	UserIDType	UserID;
	///状态信息
	ErrorMsgType	StatusMsg;
};

///交易所批量报单操作
struct ExchangeBatchOrderActionField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///操作日期
	DateType	ActionDate;
	///操作时间
	TimeType	ActionTime;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///操作本地编号
	OrderLocalIDType	ActionLocalID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///报单操作状态
	OrderActionStatusType	OrderActionStatus;
	///用户代码
	UserIDType	UserID;
};

///查询批量报单操作
struct QryBatchOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///组合合约安全系数
struct CombInstrumentGuardField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///
	RatioType	GuarantRatio;
};

///组合合约安全系数查询
struct QryCombInstrumentGuardField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///输入的申请组合
struct InputCombActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///组合引用
	OrderRefType	CombActionRef;
	///用户代码
	UserIDType	UserID;
	///买卖方向
	DirectionType	Direction;
	///数量
	VolumeType	Volume;
	///组合指令方向
	CombDirectionType	CombDirection;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
};

///申请组合
struct CombActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///组合引用
	OrderRefType	CombActionRef;
	///用户代码
	UserIDType	UserID;
	///买卖方向
	DirectionType	Direction;
	///数量
	VolumeType	Volume;
	///组合指令方向
	CombDirectionType	CombDirection;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///本地申请组合编号
	OrderLocalIDType	ActionLocalID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///组合状态
	OrderActionStatusType	ActionStatus;
	///报单提示序号
	SequenceNoType	NotifySequence;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///序号
	SequenceNoType	SequenceNo;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///用户端产品信息
	ProductInfoType	UserProductInfo;
	///状态信息
	ErrorMsgType	StatusMsg;
};

///申请组合查询
struct QryCombActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///交易所申请组合信息
struct ExchangeCombActionField
{
	///买卖方向
	DirectionType	Direction;
	///数量
	VolumeType	Volume;
	///组合指令方向
	CombDirectionType	CombDirection;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///本地申请组合编号
	OrderLocalIDType	ActionLocalID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///组合状态
	OrderActionStatusType	ActionStatus;
	///报单提示序号
	SequenceNoType	NotifySequence;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///序号
	SequenceNoType	SequenceNo;
};

///交易所申请组合查询
struct QryExchangeCombActionField
{
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///交易所交易员代码
	TraderIDType	TraderID;
};

///产品报价汇率
struct ProductExchRateField
{
	///产品代码
	InstrumentIDType	ProductID;
	///报价币种类型
	CurrencyIDType	QuoteCurrencyID;
	///汇率
	ExchangeRateType	ExchangeRate;
};

///产品报价汇率查询
struct QryProductExchRateField
{
	///产品代码
	InstrumentIDType	ProductID;
};

///查询询价价差参数
struct QryForQuoteParamField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///询价价差参数
struct ForQuoteParamField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///最新价
	PriceType	LastPrice;
	///价差
	PriceType	PriceInterval;
};

///市场行情
struct MarketDataField
{
	///交易日
	DateType	TradingDay;
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///最新价
	PriceType	LastPrice;
	///上次结算价
	PriceType	PreSettlementPrice;
	///昨收盘
	PriceType	PreClosePrice;
	///昨持仓量
	LargeVolumeType	PreOpenInterest;
	///今开盘
	PriceType	OpenPrice;
	///最高价
	PriceType	HighestPrice;
	///最低价
	PriceType	LowestPrice;
	///数量
	VolumeType	Volume;
	///成交金额
	MoneyType	Turnover;
	///持仓量
	LargeVolumeType	OpenInterest;
	///今收盘
	PriceType	ClosePrice;
	///本次结算价
	PriceType	SettlementPrice;
	///涨停板价
	PriceType	UpperLimitPrice;
	///跌停板价
	PriceType	LowerLimitPrice;
	///昨虚实度
	RatioType	PreDelta;
	///今虚实度
	RatioType	CurrDelta;
	///最后修改时间
	TimeType	UpdateTime;
	///最后修改毫秒
	MillisecType	UpdateMillisec;
	///业务日期
	DateType	ActionDay;
};

///行情基础属性
struct MarketDataBaseField
{
	///交易日
	DateType	TradingDay;
	///上次结算价
	PriceType	PreSettlementPrice;
	///昨收盘
	PriceType	PreClosePrice;
	///昨持仓量
	LargeVolumeType	PreOpenInterest;
	///昨虚实度
	RatioType	PreDelta;
};

///行情静态属性
struct MarketDataStaticField
{
	///今开盘
	PriceType	OpenPrice;
	///最高价
	PriceType	HighestPrice;
	///最低价
	PriceType	LowestPrice;
	///今收盘
	PriceType	ClosePrice;
	///涨停板价
	PriceType	UpperLimitPrice;
	///跌停板价
	PriceType	LowerLimitPrice;
	///本次结算价
	PriceType	SettlementPrice;
	///今虚实度
	RatioType	CurrDelta;
};

///行情最新成交属性
struct MarketDataLastMatchField
{
	///最新价
	PriceType	LastPrice;
	///数量
	VolumeType	Volume;
	///成交金额
	MoneyType	Turnover;
	///持仓量
	LargeVolumeType	OpenInterest;
};

///行情最优价属性
struct MarketDataBestPriceField
{
	///申买价一
	PriceType	BidPrice1;
	///申买量一
	VolumeType	BidVolume1;
	///申卖价一
	PriceType	AskPrice1;
	///申卖量一
	VolumeType	AskVolume1;
};

///行情申买二、三属性
struct MarketDataBid23Field
{
	///申买价二
	PriceType	BidPrice2;
	///申买量二
	VolumeType	BidVolume2;
	///申买价三
	PriceType	BidPrice3;
	///申买量三
	VolumeType	BidVolume3;
};

///行情申卖二、三属性
struct MarketDataAsk23Field
{
	///申卖价二
	PriceType	AskPrice2;
	///申卖量二
	VolumeType	AskVolume2;
	///申卖价三
	PriceType	AskPrice3;
	///申卖量三
	VolumeType	AskVolume3;
};

///行情申买四、五属性
struct MarketDataBid45Field
{
	///申买价四
	PriceType	BidPrice4;
	///申买量四
	VolumeType	BidVolume4;
	///申买价五
	PriceType	BidPrice5;
	///申买量五
	VolumeType	BidVolume5;
};

///行情申卖四、五属性
struct MarketDataAsk45Field
{
	///申卖价四
	PriceType	AskPrice4;
	///申卖量四
	VolumeType	AskVolume4;
	///申卖价五
	PriceType	AskPrice5;
	///申卖量五
	VolumeType	AskVolume5;
};

///行情更新时间属性
struct MarketDataUpdateTimeField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///最后修改时间
	TimeType	UpdateTime;
	///最后修改毫秒
	MillisecType	UpdateMillisec;
	///业务日期
	DateType	ActionDay;
};

///行情交易所代码属性
struct MarketDataExchangeField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///指定的合约
struct SpecificInstrumentField
{
	///合约代码
	InstrumentIDType	InstrumentID;
};

///合约状态
struct InstrumentStatusField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///结算组代码
	SettlementGroupIDType	SettlementGroupID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///合约交易状态
	InstrumentStatusType	InstrumentStatus;
	///交易阶段编号
	TradingSegmentSNType	TradingSegmentSN;
	///进入本状态时间
	TimeType	EnterTime;
	///进入本状态原因
	InstStatusEnterReasonType	EnterReason;
};

///查询合约状态
struct QryInstrumentStatusField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
};

///投资者账户
struct InvestorAccountField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///投资者帐号
	AccountIDType	AccountID;
	///币种代码
	CurrencyIDType	CurrencyID;
};

///浮动盈亏算法
struct PositionProfitAlgorithmField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者帐号
	AccountIDType	AccountID;
	///盈亏算法
	AlgorithmType	Algorithm;
	///备注
	MemoType	Memo;
	///币种代码
	CurrencyIDType	CurrencyID;
};

///会员资金折扣
struct DiscountField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///投资者代码
	InvestorIDType	InvestorID;
	///资金折扣比例
	RatioType	Discount;
};

///查询转帐银行
struct QryTransferBankField
{
	///银行代码
	BankIDType	BankID;
	///银行分中心代码
	BankBrchIDType	BankBrchID;
};

///转帐银行
struct TransferBankField
{
	///银行代码
	BankIDType	BankID;
	///银行分中心代码
	BankBrchIDType	BankBrchID;
	///银行名称
	BankNameType	BankName;
	///是否活跃
	BoolType	IsActive;
};

///查询投资者持仓明细
struct QryInvestorPositionDetailField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///投资者持仓明细
struct InvestorPositionDetailField
{
	///合约代码
	InstrumentIDType	InstrumentID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///买卖
	DirectionType	Direction;
	///开仓日期
	DateType	OpenDate;
	///成交编号
	TradeIDType	TradeID;
	///数量
	VolumeType	Volume;
	///开仓价
	PriceType	OpenPrice;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///成交类型
	TradeTypeType	TradeType;
	///组合合约代码
	InstrumentIDType	CombInstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///逐日盯市平仓盈亏
	MoneyType	CloseProfitByDate;
	///逐笔对冲平仓盈亏
	MoneyType	CloseProfitByTrade;
	///逐日盯市持仓盈亏
	MoneyType	PositionProfitByDate;
	///逐笔对冲持仓盈亏
	MoneyType	PositionProfitByTrade;
	///投资者保证金
	MoneyType	Margin;
	///交易所保证金
	MoneyType	ExchMargin;
	///保证金率
	RatioType	MarginRateByMoney;
	///保证金率(按手数)
	RatioType	MarginRateByVolume;
	///昨结算价
	PriceType	LastSettlementPrice;
	///结算价
	PriceType	SettlementPrice;
	///平仓量
	VolumeType	CloseVolume;
	///平仓金额
	MoneyType	CloseAmount;
};

///资金账户口令域
struct TradingAccountPasswordField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者帐号
	AccountIDType	AccountID;
	///密码
	PasswordType	Password;
	///币种代码
	CurrencyIDType	CurrencyID;
};

///交易所行情报盘机
struct MDTraderOfferField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///密码
	PasswordType	Password;
	///安装编号
	InstallIDType	InstallID;
	///本地报单编号
	OrderLocalIDType	OrderLocalID;
	///交易所交易员连接状态
	TraderConnectStatusType	TraderConnectStatus;
	///发出连接请求的日期
	DateType	ConnectRequestDate;
	///发出连接请求的时间
	TimeType	ConnectRequestTime;
	///上次报告日期
	DateType	LastReportDate;
	///上次报告时间
	TimeType	LastReportTime;
	///完成连接日期
	DateType	ConnectDate;
	///完成连接时间
	TimeType	ConnectTime;
	///启动日期
	DateType	StartDate;
	///启动时间
	TimeType	StartTime;
	///交易日
	DateType	TradingDay;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///本席位最大成交编号
	TradeIDType	MaxTradeID;
	///本席位最大报单备拷
	ReturnCodeType	MaxOrderMessageReference;
};

///查询行情报盘机
struct QryMDTraderOfferField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///交易所交易员代码
	TraderIDType	TraderID;
};

///查询客户通知
struct QryNoticeField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
};

///客户通知
struct NoticeField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///消息正文
	ContentType	Content;
	///经纪公司通知内容序列号
	SequenceLabelType	SequenceLabel;
};

///用户权限
struct UserRightField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///客户权限类型
	UserRightTypeType	UserRightType;
	///是否禁止
	BoolType	IsForbidden;
};

///查询结算信息确认域
struct QrySettlementInfoConfirmField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
};

///装载结算信息
struct LoadSettlementInfoField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
};

///经纪公司可提资金算法表
struct BrokerWithdrawAlgorithmField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///可提资金算法
	AlgorithmType	WithdrawAlgorithm;
	///资金使用率
	RatioType	UsingRatio;
	///可提是否包含平仓盈利
	IncludeCloseProfitType	IncludeCloseProfit;
	///本日无仓且无成交客户是否受可提比例限制
	AllWithoutTradeType	AllWithoutTrade;
	///可用是否包含平仓盈利
	IncludeCloseProfitType	AvailIncludeCloseProfit;
	///是否启用用户事件
	BoolType	IsBrokerUserEvent;
	///币种代码
	CurrencyIDType	CurrencyID;
	///货币质押比率
	RatioType	FundMortgageRatio;
	///权益算法
	BalanceAlgorithmType	BalanceAlgorithm;
};

///资金账户口令变更域
struct TradingAccountPasswordUpdateV1Field
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///原来的口令
	PasswordType	OldPassword;
	///新的口令
	PasswordType	NewPassword;
};

///资金账户口令变更域
struct TradingAccountPasswordUpdateField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者帐号
	AccountIDType	AccountID;
	///原来的口令
	PasswordType	OldPassword;
	///新的口令
	PasswordType	NewPassword;
	///币种代码
	CurrencyIDType	CurrencyID;
};

///查询组合合约分腿
struct QryCombinationLegField
{
	///组合合约代码
	InstrumentIDType	CombInstrumentID;
	///单腿编号
	LegIDType	LegID;
	///单腿合约代码
	InstrumentIDType	LegInstrumentID;
};

///查询组合合约分腿
struct QrySyncStatusField
{
	///交易日
	DateType	TradingDay;
};

///组合交易合约的单腿
struct CombinationLegField
{
	///组合合约代码
	InstrumentIDType	CombInstrumentID;
	///单腿编号
	LegIDType	LegID;
	///单腿合约代码
	InstrumentIDType	LegInstrumentID;
	///买卖方向
	DirectionType	Direction;
	///单腿乘数
	LegMultipleType	LegMultiple;
	///派生层数
	ImplyLevelType	ImplyLevel;
};

///数据同步状态
struct SyncStatusField
{
	///交易日
	DateType	TradingDay;
	///数据同步状态
	DataSyncStatusType	DataSyncStatus;
};

///查询联系人
struct QryLinkManField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
};

///联系人
struct LinkManField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///联系人类型
	PersonTypeType	PersonType;
	///证件类型
	IdCardTypeType	IdentifiedCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///名称
	PartyNameType	PersonName;
	///联系电话
	TelephoneType	Telephone;
	///通讯地址
	AddressType	Address;
	///邮政编码
	ZipCodeType	ZipCode;
	///优先级
	PriorityType	Priority;
	///开户邮政编码
	UOAZipCodeType	UOAZipCode;
	///全称
	InvestorFullNameType	PersonFullName;
};

///查询经纪公司用户事件
struct QryBrokerUserEventField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///用户事件类型
	UserEventTypeType	UserEventType;
};

///查询经纪公司用户事件
struct BrokerUserEventField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///用户事件类型
	UserEventTypeType	UserEventType;
	///用户事件序号
	SequenceNoType	EventSequenceNo;
	///事件发生日期
	DateType	EventDate;
	///事件发生时间
	TimeType	EventTime;
	///用户事件信息
	UserEventInfoType	UserEventInfo;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///查询签约银行请求
struct QryContractBankField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///银行代码
	BankIDType	BankID;
	///银行分中心代码
	BankBrchIDType	BankBrchID;
};

///查询签约银行响应
struct ContractBankField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///银行代码
	BankIDType	BankID;
	///银行分中心代码
	BankBrchIDType	BankBrchID;
	///银行名称
	BankNameType	BankName;
};

///投资者组合持仓明细
struct InvestorPositionCombineDetailField
{
	///交易日
	DateType	TradingDay;
	///开仓日期
	DateType	OpenDate;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///结算编号
	SettlementIDType	SettlementID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///组合编号
	TradeIDType	ComTradeID;
	///撮合编号
	TradeIDType	TradeID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///买卖
	DirectionType	Direction;
	///持仓量
	VolumeType	TotalAmt;
	///投资者保证金
	MoneyType	Margin;
	///交易所保证金
	MoneyType	ExchMargin;
	///保证金率
	RatioType	MarginRateByMoney;
	///保证金率(按手数)
	RatioType	MarginRateByVolume;
	///单腿编号
	LegIDType	LegID;
	///单腿乘数
	LegMultipleType	LegMultiple;
	///组合持仓合约编码
	InstrumentIDType	CombInstrumentID;
	///成交组号
	TradeGroupIDType	TradeGroupID;
};

///预埋单
struct ParkedOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///报单引用
	OrderRefType	OrderRef;
	///用户代码
	UserIDType	UserID;
	///报单价格条件
	OrderPriceTypeType	OrderPriceType;
	///买卖方向
	DirectionType	Direction;
	///组合开平标志
	CombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	CombHedgeFlagType	CombHedgeFlag;
	///价格
	PriceType	LimitPrice;
	///数量
	VolumeType	VolumeTotalOriginal;
	///有效期类型
	TimeConditionType	TimeCondition;
	///GTD日期
	DateType	GTDDate;
	///成交量类型
	VolumeConditionType	VolumeCondition;
	///最小成交量
	VolumeType	MinVolume;
	///触发条件
	ContingentConditionType	ContingentCondition;
	///止损价
	PriceType	StopPrice;
	///强平原因
	ForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	BoolType	IsAutoSuspend;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///请求编号
	RequestIDType	RequestID;
	///用户强评标志
	BoolType	UserForceClose;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///预埋报单编号
	ParkedOrderIDType	ParkedOrderID;
	///用户类型
	UserTypeType	UserType;
	///预埋单状态
	ParkedOrderStatusType	Status;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
	///互换单标志
	BoolType	IsSwapOrder;
};

///输入预埋单操作
struct ParkedOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///报单操作引用
	OrderActionRefType	OrderActionRef;
	///报单引用
	OrderRefType	OrderRef;
	///请求编号
	RequestIDType	RequestID;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///报单编号
	OrderSysIDType	OrderSysID;
	///操作标志
	ActionFlagType	ActionFlag;
	///价格
	PriceType	LimitPrice;
	///数量变化
	VolumeType	VolumeChange;
	///用户代码
	UserIDType	UserID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///预埋撤单单编号
	ParkedOrderActionIDType	ParkedOrderActionID;
	///用户类型
	UserTypeType	UserType;
	///预埋撤单状态
	ParkedOrderStatusType	Status;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///查询预埋单
struct QryParkedOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///查询预埋撤单
struct QryParkedOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///删除预埋单
struct RemoveParkedOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///预埋报单编号
	ParkedOrderIDType	ParkedOrderID;
};

///删除预埋撤单
struct RemoveParkedOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///预埋撤单编号
	ParkedOrderActionIDType	ParkedOrderActionID;
};

///经纪公司可提资金算法表
struct InvestorWithdrawAlgorithmField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///投资者代码
	InvestorIDType	InvestorID;
	///可提资金比例
	RatioType	UsingRatio;
	///币种代码
	CurrencyIDType	CurrencyID;
	///货币质押比率
	RatioType	FundMortgageRatio;
};

///查询组合持仓明细
struct QryInvestorPositionCombineDetailField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///组合持仓合约编码
	InstrumentIDType	CombInstrumentID;
};

///成交均价
struct MarketDataAveragePriceField
{
	///当日均价
	PriceType	AveragePrice;
};

///校验投资者密码
struct VerifyInvestorPasswordField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///密码
	PasswordType	Password;
};

///用户IP
struct UserIPField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///IP地址
	IPAddressType	IPAddress;
	///IP地址掩码
	IPAddressType	IPMask;
	///Mac地址
	MacAddressType	MacAddress;
};

///用户事件通知信息
struct TradingNoticeInfoField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///发送时间
	TimeType	SendTime;
	///消息正文
	ContentType	FieldContent;
	///序列系列号
	SequenceSeriesType	SequenceSeries;
	///序列号
	SequenceNoType	SequenceNo;
};

///用户事件通知
struct TradingNoticeField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者范围
	InvestorRangeType	InvestorRange;
	///投资者代码
	InvestorIDType	InvestorID;
	///序列系列号
	SequenceSeriesType	SequenceSeries;
	///用户代码
	UserIDType	UserID;
	///发送时间
	TimeType	SendTime;
	///序列号
	SequenceNoType	SequenceNo;
	///消息正文
	ContentType	FieldContent;
};

///查询交易事件通知
struct QryTradingNoticeField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
};

///查询错误报单
struct QryErrOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
};

///错误报单
struct ErrOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///报单引用
	OrderRefType	OrderRef;
	///用户代码
	UserIDType	UserID;
	///报单价格条件
	OrderPriceTypeType	OrderPriceType;
	///买卖方向
	DirectionType	Direction;
	///组合开平标志
	CombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	CombHedgeFlagType	CombHedgeFlag;
	///价格
	PriceType	LimitPrice;
	///数量
	VolumeType	VolumeTotalOriginal;
	///有效期类型
	TimeConditionType	TimeCondition;
	///GTD日期
	DateType	GTDDate;
	///成交量类型
	VolumeConditionType	VolumeCondition;
	///最小成交量
	VolumeType	MinVolume;
	///触发条件
	ContingentConditionType	ContingentCondition;
	///止损价
	PriceType	StopPrice;
	///强平原因
	ForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	BoolType	IsAutoSuspend;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///请求编号
	RequestIDType	RequestID;
	///用户强评标志
	BoolType	UserForceClose;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
	///互换单标志
	BoolType	IsSwapOrder;
};

///查询错误报单操作
struct ErrorConditionalOrderField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///报单引用
	OrderRefType	OrderRef;
	///用户代码
	UserIDType	UserID;
	///报单价格条件
	OrderPriceTypeType	OrderPriceType;
	///买卖方向
	DirectionType	Direction;
	///组合开平标志
	CombOffsetFlagType	CombOffsetFlag;
	///组合投机套保标志
	CombHedgeFlagType	CombHedgeFlag;
	///价格
	PriceType	LimitPrice;
	///数量
	VolumeType	VolumeTotalOriginal;
	///有效期类型
	TimeConditionType	TimeCondition;
	///GTD日期
	DateType	GTDDate;
	///成交量类型
	VolumeConditionType	VolumeCondition;
	///最小成交量
	VolumeType	MinVolume;
	///触发条件
	ContingentConditionType	ContingentCondition;
	///止损价
	PriceType	StopPrice;
	///强平原因
	ForceCloseReasonType	ForceCloseReason;
	///自动挂起标志
	BoolType	IsAutoSuspend;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///请求编号
	RequestIDType	RequestID;
	///本地报单编号
	OrderLocalIDType	OrderLocalID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///合约在交易所的代码
	ExchangeInstIDType	ExchangeInstID;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///报单提交状态
	OrderSubmitStatusType	OrderSubmitStatus;
	///报单提示序号
	SequenceNoType	NotifySequence;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///报单编号
	OrderSysIDType	OrderSysID;
	///报单来源
	OrderSourceType	OrderSource;
	///报单状态
	OrderStatusType	OrderStatus;
	///报单类型
	OrderTypeType	OrderType;
	///今成交数量
	VolumeType	VolumeTraded;
	///剩余数量
	VolumeType	VolumeTotal;
	///报单日期
	DateType	InsertDate;
	///委托时间
	TimeType	InsertTime;
	///激活时间
	TimeType	ActiveTime;
	///挂起时间
	TimeType	SuspendTime;
	///最后修改时间
	TimeType	UpdateTime;
	///撤销时间
	TimeType	CancelTime;
	///最后修改交易所交易员代码
	TraderIDType	ActiveTraderID;
	///结算会员编号
	ParticipantIDType	ClearingPartID;
	///序号
	SequenceNoType	SequenceNo;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///用户端产品信息
	ProductInfoType	UserProductInfo;
	///状态信息
	ErrorMsgType	StatusMsg;
	///用户强评标志
	BoolType	UserForceClose;
	///操作用户代码
	UserIDType	ActiveUserID;
	///经纪公司报单编号
	SequenceNoType	BrokerOrderSeq;
	///相关报单
	OrderSysIDType	RelativeOrderSysID;
	///郑商所成交数量
	VolumeType	ZCETotalTradedVolume;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
	///互换单标志
	BoolType	IsSwapOrder;
};

///查询错误报单操作
struct QryErrOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
};

///错误报单操作
struct ErrOrderActionField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///报单操作引用
	OrderActionRefType	OrderActionRef;
	///报单引用
	OrderRefType	OrderRef;
	///请求编号
	RequestIDType	RequestID;
	///前置编号
	FrontIDType	FrontID;
	///会话编号
	SessionIDType	SessionID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///报单编号
	OrderSysIDType	OrderSysID;
	///操作标志
	ActionFlagType	ActionFlag;
	///价格
	PriceType	LimitPrice;
	///数量变化
	VolumeType	VolumeChange;
	///操作日期
	DateType	ActionDate;
	///操作时间
	TimeType	ActionTime;
	///交易所交易员代码
	TraderIDType	TraderID;
	///安装编号
	InstallIDType	InstallID;
	///本地报单编号
	OrderLocalIDType	OrderLocalID;
	///操作本地编号
	OrderLocalIDType	ActionLocalID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///客户代码
	ClientIDType	ClientID;
	///业务单元
	BusinessUnitType	BusinessUnit;
	///报单操作状态
	OrderActionStatusType	OrderActionStatus;
	///用户代码
	UserIDType	UserID;
	///状态信息
	ErrorMsgType	StatusMsg;
	///合约代码
	InstrumentIDType	InstrumentID;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///查询交易所状态
struct QryExchangeSequenceField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///交易所状态
struct ExchangeSequenceField
{
	///交易所代码
	ExchangeIDType	ExchangeID;
	///序号
	SequenceNoType	SequenceNo;
	///合约交易状态
	InstrumentStatusType	MarketStatus;
};

///根据价格查询最大报单数量
struct QueryMaxOrderVolumeWithPriceField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///买卖方向
	DirectionType	Direction;
	///开平标志
	OffsetFlagType	OffsetFlag;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///最大允许报单数量
	VolumeType	MaxVolume;
	///报单价格
	PriceType	Price;
};

///查询经纪公司交易参数
struct QryBrokerTradingParamsField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///币种代码
	CurrencyIDType	CurrencyID;
};

///经纪公司交易参数
struct BrokerTradingParamsField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///保证金价格类型
	MarginPriceTypeType	MarginPriceType;
	///盈亏算法
	AlgorithmType	Algorithm;
	///可用是否包含平仓盈利
	IncludeCloseProfitType	AvailIncludeCloseProfit;
	///币种代码
	CurrencyIDType	CurrencyID;
	///期权权利金价格类型
	OptionRoyaltyPriceTypeType	OptionRoyaltyPriceType;
};

///查询经纪公司交易算法
struct QryBrokerTradingAlgosField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///经纪公司交易算法
struct BrokerTradingAlgosField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///持仓处理算法编号
	HandlePositionAlgoIDType	HandlePositionAlgoID;
	///寻找保证金率算法编号
	FindMarginRateAlgoIDType	FindMarginRateAlgoID;
	///资金处理算法编号
	HandleTradingAccountAlgoIDType	HandleTradingAccountAlgoID;
};

///查询经纪公司资金
struct QueryBrokerDepositField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///经纪公司资金
struct BrokerDepositField
{
	///交易日期
	TradeDateType	TradingDay;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///会员代码
	ParticipantIDType	ParticipantID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///上次结算准备金
	MoneyType	PreBalance;
	///当前保证金总额
	MoneyType	CurrMargin;
	///平仓盈亏
	MoneyType	CloseProfit;
	///期货结算准备金
	MoneyType	Balance;
	///入金金额
	MoneyType	Deposit;
	///出金金额
	MoneyType	Withdraw;
	///可提资金
	MoneyType	Available;
	///基本准备金
	MoneyType	Reserve;
	///冻结的保证金
	MoneyType	FrozenMargin;
};

///查询保证金监管系统经纪公司密钥
struct QryCFMMCBrokerKeyField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
};

///保证金监管系统经纪公司密钥
struct CFMMCBrokerKeyField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///经纪公司统一编码
	ParticipantIDType	ParticipantID;
	///密钥生成日期
	DateType	CreateDate;
	///密钥生成时间
	TimeType	CreateTime;
	///密钥编号
	SequenceNoType	KeyID;
	///动态密钥
	CFMMCKeyType	CurrentKey;
	///动态密钥类型
	CFMMCKeyKindType	KeyKind;
};

///保证金监管系统经纪公司资金账户密钥
struct CFMMCTradingAccountKeyField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///经纪公司统一编码
	ParticipantIDType	ParticipantID;
	///投资者帐号
	AccountIDType	AccountID;
	///密钥编号
	SequenceNoType	KeyID;
	///动态密钥
	CFMMCKeyType	CurrentKey;
};

///请求查询保证金监管系统经纪公司资金账户密钥
struct QryCFMMCTradingAccountKeyField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
};

///用户动态令牌参数
struct BrokerUserOTPParamField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///动态令牌提供商
	OTPVendorsIDType	OTPVendorsID;
	///动态令牌序列号
	SerialNumberType	SerialNumber;
	///令牌密钥
	AuthKeyType	AuthKey;
	///漂移值
	LastDriftType	LastDrift;
	///成功值
	LastSuccessType	LastSuccess;
	///动态令牌类型
	OTPTypeType	OTPType;
};

///手工同步用户动态令牌
struct ManualSyncBrokerUserOTPField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///动态令牌类型
	OTPTypeType	OTPType;
	///第一个动态密码
	PasswordType	FirstOTP;
	///第二个动态密码
	PasswordType	SecondOTP;
};

///投资者手续费率模板
struct CommRateModelField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///手续费率模板代码
	InvestorIDType	CommModelID;
	///模板名称
	CommModelNameType	CommModelName;
};

///请求查询投资者手续费率模板
struct QryCommRateModelField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///手续费率模板代码
	InvestorIDType	CommModelID;
};

///投资者保证金率模板
struct MarginModelField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///保证金率模板代码
	InvestorIDType	MarginModelID;
	///模板名称
	CommModelNameType	MarginModelName;
};

///请求查询投资者保证金率模板
struct QryMarginModelField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///保证金率模板代码
	InvestorIDType	MarginModelID;
};

///仓单折抵信息
struct EWarrantOffsetField
{
	///交易日期
	TradeDateType	TradingDay;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///合约代码
	InstrumentIDType	InstrumentID;
	///买卖方向
	DirectionType	Direction;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
	///数量
	VolumeType	Volume;
};

///查询仓单折抵信息
struct QryEWarrantOffsetField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///合约代码
	InstrumentIDType	InstrumentID;
};

///查询投资者品种/跨品种保证金
struct QryInvestorProductGroupMarginField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///品种/跨品种标示
	InstrumentIDType	ProductGroupID;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
};

///投资者品种/跨品种保证金
struct InvestorProductGroupMarginField
{
	///品种/跨品种标示
	InstrumentIDType	ProductGroupID;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///交易日
	DateType	TradingDay;
	///结算编号
	SettlementIDType	SettlementID;
	///冻结的保证金
	MoneyType	FrozenMargin;
	///多头冻结的保证金
	MoneyType	LongFrozenMargin;
	///空头冻结的保证金
	MoneyType	ShortFrozenMargin;
	///占用的保证金
	MoneyType	UseMargin;
	///多头保证金
	MoneyType	LongUseMargin;
	///空头保证金
	MoneyType	ShortUseMargin;
	///交易所保证金
	MoneyType	ExchMargin;
	///交易所多头保证金
	MoneyType	LongExchMargin;
	///交易所空头保证金
	MoneyType	ShortExchMargin;
	///平仓盈亏
	MoneyType	CloseProfit;
	///冻结的手续费
	MoneyType	FrozenCommission;
	///手续费
	MoneyType	Commission;
	///冻结的资金
	MoneyType	FrozenCash;
	///资金差额
	MoneyType	CashIn;
	///持仓盈亏
	MoneyType	PositionProfit;
	///折抵总金额
	MoneyType	OffsetAmount;
	///多头折抵总金额
	MoneyType	LongOffsetAmount;
	///空头折抵总金额
	MoneyType	ShortOffsetAmount;
	///交易所折抵总金额
	MoneyType	ExchOffsetAmount;
	///交易所多头折抵总金额
	MoneyType	LongExchOffsetAmount;
	///交易所空头折抵总金额
	MoneyType	ShortExchOffsetAmount;
	///投机套保标志
	HedgeFlagType	HedgeFlag;
};

///查询监控中心用户令牌
struct QueryCFMMCTradingAccountTokenField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
};

///监控中心用户令牌
struct CFMMCTradingAccountTokenField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///经纪公司统一编码
	ParticipantIDType	ParticipantID;
	///投资者帐号
	AccountIDType	AccountID;
	///密钥编号
	SequenceNoType	KeyID;
	///动态令牌
	CFMMCTokenType	Token;
};

///查询产品组
struct QryProductGroupField
{
	///产品代码
	InstrumentIDType	ProductID;
	///交易所代码
	ExchangeIDType	ExchangeID;
};

///投资者品种/跨品种保证金产品组
struct ProductGroupField
{
	///产品代码
	InstrumentIDType	ProductID;
	///交易所代码
	ExchangeIDType	ExchangeID;
	///产品组代码
	InstrumentIDType	ProductGroupID;
};

///转帐开户请求
struct ReqOpenAccountField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///性别
	GenderType	Gender;
	///国家代码
	CountryCodeType	CountryCode;
	///客户类型
	CustTypeType	CustType;
	///地址
	AddressType	Address;
	///邮编
	ZipCodeType	ZipCode;
	///电话号码
	TelephoneType	Telephone;
	///手机
	MobilePhoneType	MobilePhone;
	///传真
	FaxType	Fax;
	///电子邮件
	EMailType	EMail;
	///资金账户状态
	MoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///安装编号
	InstallIDType	InstallID;
	///验证客户证件号码标志
	YesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	CurrencyIDType	CurrencyID;
	///汇钞标志
	CashExchangeCodeType	CashExchangeCode;
	///摘要
	DigestType	Digest;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货单位帐号类型
	BankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	BankAccountType	BankSecuAcc;
	///银行密码标志
	PwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	PwdFlagType	SecuPwdFlag;
	///交易柜员
	OperNoType	OperNo;
	///交易ID
	TIDType	TID;
	///用户标识
	UserIDType	UserID;
};

///转帐销户请求
struct ReqCancelAccountField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///性别
	GenderType	Gender;
	///国家代码
	CountryCodeType	CountryCode;
	///客户类型
	CustTypeType	CustType;
	///地址
	AddressType	Address;
	///邮编
	ZipCodeType	ZipCode;
	///电话号码
	TelephoneType	Telephone;
	///手机
	MobilePhoneType	MobilePhone;
	///传真
	FaxType	Fax;
	///电子邮件
	EMailType	EMail;
	///资金账户状态
	MoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///安装编号
	InstallIDType	InstallID;
	///验证客户证件号码标志
	YesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	CurrencyIDType	CurrencyID;
	///汇钞标志
	CashExchangeCodeType	CashExchangeCode;
	///摘要
	DigestType	Digest;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货单位帐号类型
	BankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	BankAccountType	BankSecuAcc;
	///银行密码标志
	PwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	PwdFlagType	SecuPwdFlag;
	///交易柜员
	OperNoType	OperNo;
	///交易ID
	TIDType	TID;
	///用户标识
	UserIDType	UserID;
};

///变更银行账户请求
struct ReqChangeAccountField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///性别
	GenderType	Gender;
	///国家代码
	CountryCodeType	CountryCode;
	///客户类型
	CustTypeType	CustType;
	///地址
	AddressType	Address;
	///邮编
	ZipCodeType	ZipCode;
	///电话号码
	TelephoneType	Telephone;
	///手机
	MobilePhoneType	MobilePhone;
	///传真
	FaxType	Fax;
	///电子邮件
	EMailType	EMail;
	///资金账户状态
	MoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///新银行帐号
	BankAccountType	NewBankAccount;
	///新银行密码
	PasswordType	NewBankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///安装编号
	InstallIDType	InstallID;
	///验证客户证件号码标志
	YesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	CurrencyIDType	CurrencyID;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///银行密码标志
	PwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	PwdFlagType	SecuPwdFlag;
	///交易ID
	TIDType	TID;
	///摘要
	DigestType	Digest;
};

///转账请求
struct ReqTransferField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	CustTypeType	CustType;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///安装编号
	InstallIDType	InstallID;
	///期货公司流水号
	FutureSerialType	FutureSerial;
	///用户标识
	UserIDType	UserID;
	///验证客户证件号码标志
	YesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	CurrencyIDType	CurrencyID;
	///转帐金额
	TradeAmountType	TradeAmount;
	///期货可取金额
	TradeAmountType	FutureFetchAmount;
	///费用支付标志
	FeePayFlagType	FeePayFlag;
	///应收客户费用
	CustFeeType	CustFee;
	///应收期货公司费用
	FutureFeeType	BrokerFee;
	///发送方给接收方的消息
	AddInfoType	Message;
	///摘要
	DigestType	Digest;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货单位帐号类型
	BankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	BankAccountType	BankSecuAcc;
	///银行密码标志
	PwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	PwdFlagType	SecuPwdFlag;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
	///转账交易状态
	TransferStatusType	TransferStatus;
};

///银行发起银行资金转期货响应
struct RspTransferField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	CustTypeType	CustType;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///安装编号
	InstallIDType	InstallID;
	///期货公司流水号
	FutureSerialType	FutureSerial;
	///用户标识
	UserIDType	UserID;
	///验证客户证件号码标志
	YesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	CurrencyIDType	CurrencyID;
	///转帐金额
	TradeAmountType	TradeAmount;
	///期货可取金额
	TradeAmountType	FutureFetchAmount;
	///费用支付标志
	FeePayFlagType	FeePayFlag;
	///应收客户费用
	CustFeeType	CustFee;
	///应收期货公司费用
	FutureFeeType	BrokerFee;
	///发送方给接收方的消息
	AddInfoType	Message;
	///摘要
	DigestType	Digest;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货单位帐号类型
	BankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	BankAccountType	BankSecuAcc;
	///银行密码标志
	PwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	PwdFlagType	SecuPwdFlag;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
	///转账交易状态
	TransferStatusType	TransferStatus;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///冲正请求
struct ReqRepealField
{
	///冲正时间间隔
	RepealTimeIntervalType	RepealTimeInterval;
	///已经冲正次数
	RepealedTimesType	RepealedTimes;
	///银行冲正标志
	BankRepealFlagType	BankRepealFlag;
	///期商冲正标志
	BrokerRepealFlagType	BrokerRepealFlag;
	///被冲正平台流水号
	PlateSerialType	PlateRepealSerial;
	///被冲正银行流水号
	BankSerialType	BankRepealSerial;
	///被冲正期货流水号
	FutureSerialType	FutureRepealSerial;
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	CustTypeType	CustType;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///安装编号
	InstallIDType	InstallID;
	///期货公司流水号
	FutureSerialType	FutureSerial;
	///用户标识
	UserIDType	UserID;
	///验证客户证件号码标志
	YesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	CurrencyIDType	CurrencyID;
	///转帐金额
	TradeAmountType	TradeAmount;
	///期货可取金额
	TradeAmountType	FutureFetchAmount;
	///费用支付标志
	FeePayFlagType	FeePayFlag;
	///应收客户费用
	CustFeeType	CustFee;
	///应收期货公司费用
	FutureFeeType	BrokerFee;
	///发送方给接收方的消息
	AddInfoType	Message;
	///摘要
	DigestType	Digest;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货单位帐号类型
	BankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	BankAccountType	BankSecuAcc;
	///银行密码标志
	PwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	PwdFlagType	SecuPwdFlag;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
	///转账交易状态
	TransferStatusType	TransferStatus;
};

///冲正响应
struct RspRepealField
{
	///冲正时间间隔
	RepealTimeIntervalType	RepealTimeInterval;
	///已经冲正次数
	RepealedTimesType	RepealedTimes;
	///银行冲正标志
	BankRepealFlagType	BankRepealFlag;
	///期商冲正标志
	BrokerRepealFlagType	BrokerRepealFlag;
	///被冲正平台流水号
	PlateSerialType	PlateRepealSerial;
	///被冲正银行流水号
	BankSerialType	BankRepealSerial;
	///被冲正期货流水号
	FutureSerialType	FutureRepealSerial;
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	CustTypeType	CustType;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///安装编号
	InstallIDType	InstallID;
	///期货公司流水号
	FutureSerialType	FutureSerial;
	///用户标识
	UserIDType	UserID;
	///验证客户证件号码标志
	YesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	CurrencyIDType	CurrencyID;
	///转帐金额
	TradeAmountType	TradeAmount;
	///期货可取金额
	TradeAmountType	FutureFetchAmount;
	///费用支付标志
	FeePayFlagType	FeePayFlag;
	///应收客户费用
	CustFeeType	CustFee;
	///应收期货公司费用
	FutureFeeType	BrokerFee;
	///发送方给接收方的消息
	AddInfoType	Message;
	///摘要
	DigestType	Digest;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货单位帐号类型
	BankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	BankAccountType	BankSecuAcc;
	///银行密码标志
	PwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	PwdFlagType	SecuPwdFlag;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
	///转账交易状态
	TransferStatusType	TransferStatus;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///查询账户信息请求
struct ReqQueryAccountField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	CustTypeType	CustType;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///期货公司流水号
	FutureSerialType	FutureSerial;
	///安装编号
	InstallIDType	InstallID;
	///用户标识
	UserIDType	UserID;
	///验证客户证件号码标志
	YesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	CurrencyIDType	CurrencyID;
	///摘要
	DigestType	Digest;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货单位帐号类型
	BankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	BankAccountType	BankSecuAcc;
	///银行密码标志
	PwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	PwdFlagType	SecuPwdFlag;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
};

///查询账户信息响应
struct RspQueryAccountField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	CustTypeType	CustType;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///期货公司流水号
	FutureSerialType	FutureSerial;
	///安装编号
	InstallIDType	InstallID;
	///用户标识
	UserIDType	UserID;
	///验证客户证件号码标志
	YesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	CurrencyIDType	CurrencyID;
	///摘要
	DigestType	Digest;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货单位帐号类型
	BankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	BankAccountType	BankSecuAcc;
	///银行密码标志
	PwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	PwdFlagType	SecuPwdFlag;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
	///银行可用金额
	TradeAmountType	BankUseAmount;
	///银行可取金额
	TradeAmountType	BankFetchAmount;
};

///期商签到签退
struct FutureSignIOField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///安装编号
	InstallIDType	InstallID;
	///用户标识
	UserIDType	UserID;
	///摘要
	DigestType	Digest;
	///币种代码
	CurrencyIDType	CurrencyID;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
};

///期商签到响应
struct RspFutureSignInField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///安装编号
	InstallIDType	InstallID;
	///用户标识
	UserIDType	UserID;
	///摘要
	DigestType	Digest;
	///币种代码
	CurrencyIDType	CurrencyID;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
	///PIN密钥
	PasswordKeyType	PinKey;
	///MAC密钥
	PasswordKeyType	MacKey;
};

///期商签退请求
struct ReqFutureSignOutField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///安装编号
	InstallIDType	InstallID;
	///用户标识
	UserIDType	UserID;
	///摘要
	DigestType	Digest;
	///币种代码
	CurrencyIDType	CurrencyID;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
};

///期商签退响应
struct RspFutureSignOutField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///安装编号
	InstallIDType	InstallID;
	///用户标识
	UserIDType	UserID;
	///摘要
	DigestType	Digest;
	///币种代码
	CurrencyIDType	CurrencyID;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///查询指定流水号的交易结果请求
struct ReqQueryTradeResultBySerialField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///流水号
	SerialType	Reference;
	///本流水号发布者的机构类型
	InstitutionTypeType	RefrenceIssureType;
	///本流水号发布者机构编码
	OrganCodeType	RefrenceIssure;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	CustTypeType	CustType;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///币种代码
	CurrencyIDType	CurrencyID;
	///转帐金额
	TradeAmountType	TradeAmount;
	///摘要
	DigestType	Digest;
};

///查询指定流水号的交易结果响应
struct RspQueryTradeResultBySerialField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
	///流水号
	SerialType	Reference;
	///本流水号发布者的机构类型
	InstitutionTypeType	RefrenceIssureType;
	///本流水号发布者机构编码
	OrganCodeType	RefrenceIssure;
	///原始返回代码
	ReturnCodeType	OriginReturnCode;
	///原始返回码描述
	DescrInfoForReturnCodeType	OriginDescrInfoForReturnCode;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///币种代码
	CurrencyIDType	CurrencyID;
	///转帐金额
	TradeAmountType	TradeAmount;
	///摘要
	DigestType	Digest;
};

///日终文件就绪请求
struct ReqDayEndFileReadyField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///文件业务功能
	FileBusinessCodeType	FileBusinessCode;
	///摘要
	DigestType	Digest;
};

///返回结果
struct ReturnResultField
{
	///返回代码
	ReturnCodeType	ReturnCode;
	///返回码描述
	DescrInfoForReturnCodeType	DescrInfoForReturnCode;
};

///验证期货资金密码
struct VerifyFuturePasswordField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///安装编号
	InstallIDType	InstallID;
	///交易ID
	TIDType	TID;
	///币种代码
	CurrencyIDType	CurrencyID;
};

///验证客户信息
struct VerifyCustInfoField
{
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	CustTypeType	CustType;
};

///验证期货资金密码和客户信息
struct VerifyFuturePasswordAndCustInfoField
{
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	CustTypeType	CustType;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///币种代码
	CurrencyIDType	CurrencyID;
};

///验证期货资金密码和客户信息
struct DepositResultInformField
{
	///出入金流水号，该流水号为银期报盘返回的流水号
	DepositSeqNoType	DepositSeqNo;
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者代码
	InvestorIDType	InvestorID;
	///入金金额
	MoneyType	Deposit;
	///请求编号
	RequestIDType	RequestID;
	///返回代码
	ReturnCodeType	ReturnCode;
	///返回码描述
	DescrInfoForReturnCodeType	DescrInfoForReturnCode;
};

///交易核心向银期报盘发出密钥同步请求
struct ReqSyncKeyField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///安装编号
	InstallIDType	InstallID;
	///用户标识
	UserIDType	UserID;
	///交易核心给银期报盘的消息
	AddInfoType	Message;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
};

///交易核心向银期报盘发出密钥同步响应
struct RspSyncKeyField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///安装编号
	InstallIDType	InstallID;
	///用户标识
	UserIDType	UserID;
	///交易核心给银期报盘的消息
	AddInfoType	Message;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///查询账户信息通知
struct NotifyQueryAccountField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///客户类型
	CustTypeType	CustType;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///期货公司流水号
	FutureSerialType	FutureSerial;
	///安装编号
	InstallIDType	InstallID;
	///用户标识
	UserIDType	UserID;
	///验证客户证件号码标志
	YesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	CurrencyIDType	CurrencyID;
	///摘要
	DigestType	Digest;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货单位帐号类型
	BankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	BankAccountType	BankSecuAcc;
	///银行密码标志
	PwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	PwdFlagType	SecuPwdFlag;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
	///银行可用金额
	TradeAmountType	BankUseAmount;
	///银行可取金额
	TradeAmountType	BankFetchAmount;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///银期转账交易流水表
struct TransferSerialField
{
	///平台流水号
	PlateSerialType	PlateSerial;
	///交易发起方日期
	TradeDateType	TradeDate;
	///交易日期
	DateType	TradingDay;
	///交易时间
	TradeTimeType	TradeTime;
	///交易代码
	TradeCodeType	TradeCode;
	///会话编号
	SessionIDType	SessionID;
	///银行编码
	BankIDType	BankID;
	///银行分支机构编码
	BankBrchIDType	BankBranchID;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///银行帐号
	BankAccountType	BankAccount;
	///银行流水号
	BankSerialType	BankSerial;
	///期货公司编码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///期货公司帐号类型
	FutureAccTypeType	FutureAccType;
	///投资者帐号
	AccountIDType	AccountID;
	///投资者代码
	InvestorIDType	InvestorID;
	///期货公司流水号
	FutureSerialType	FutureSerial;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///币种代码
	CurrencyIDType	CurrencyID;
	///交易金额
	TradeAmountType	TradeAmount;
	///应收客户费用
	CustFeeType	CustFee;
	///应收期货公司费用
	FutureFeeType	BrokerFee;
	///有效标志
	AvailabilityFlagType	AvailabilityFlag;
	///操作员
	OperatorCodeType	OperatorCode;
	///新银行帐号
	BankAccountType	BankNewAccount;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///请求查询转帐流水
struct QryTransferSerialField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者帐号
	AccountIDType	AccountID;
	///银行编码
	BankIDType	BankID;
	///币种代码
	CurrencyIDType	CurrencyID;
};

///期商签到通知
struct NotifyFutureSignInField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///安装编号
	InstallIDType	InstallID;
	///用户标识
	UserIDType	UserID;
	///摘要
	DigestType	Digest;
	///币种代码
	CurrencyIDType	CurrencyID;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
	///PIN密钥
	PasswordKeyType	PinKey;
	///MAC密钥
	PasswordKeyType	MacKey;
};

///期商签退通知
struct NotifyFutureSignOutField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///安装编号
	InstallIDType	InstallID;
	///用户标识
	UserIDType	UserID;
	///摘要
	DigestType	Digest;
	///币种代码
	CurrencyIDType	CurrencyID;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///交易核心向银期报盘发出密钥同步处理结果的通知
struct NotifySyncKeyField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///安装编号
	InstallIDType	InstallID;
	///用户标识
	UserIDType	UserID;
	///交易核心给银期报盘的消息
	AddInfoType	Message;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///交易柜员
	OperNoType	OperNo;
	///请求编号
	RequestIDType	RequestID;
	///交易ID
	TIDType	TID;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///请求查询银期签约关系
struct QryAccountregisterField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者帐号
	AccountIDType	AccountID;
	///银行编码
	BankIDType	BankID;
	///银行分支机构编码
	BankBrchIDType	BankBranchID;
	///币种代码
	CurrencyIDType	CurrencyID;
};

///客户开销户信息表
struct AccountregisterField
{
	///交易日期
	TradeDateType	TradeDay;
	///银行编码
	BankIDType	BankID;
	///银行分支机构编码
	BankBrchIDType	BankBranchID;
	///银行帐号
	BankAccountType	BankAccount;
	///期货公司编码
	BrokerIDType	BrokerID;
	///期货公司分支机构编码
	FutureBranchIDType	BrokerBranchID;
	///投资者帐号
	AccountIDType	AccountID;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///客户姓名
	IndividualNameType	CustomerName;
	///币种代码
	CurrencyIDType	CurrencyID;
	///开销户类别
	OpenOrDestroyType	OpenOrDestroy;
	///签约日期
	TradeDateType	RegDate;
	///解约日期
	TradeDateType	OutDate;
	///交易ID
	TIDType	TID;
	///客户类型
	CustTypeType	CustType;
	///银行帐号类型
	BankAccTypeType	BankAccType;
};

///银期开户信息
struct OpenAccountField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///性别
	GenderType	Gender;
	///国家代码
	CountryCodeType	CountryCode;
	///客户类型
	CustTypeType	CustType;
	///地址
	AddressType	Address;
	///邮编
	ZipCodeType	ZipCode;
	///电话号码
	TelephoneType	Telephone;
	///手机
	MobilePhoneType	MobilePhone;
	///传真
	FaxType	Fax;
	///电子邮件
	EMailType	EMail;
	///资金账户状态
	MoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///安装编号
	InstallIDType	InstallID;
	///验证客户证件号码标志
	YesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	CurrencyIDType	CurrencyID;
	///汇钞标志
	CashExchangeCodeType	CashExchangeCode;
	///摘要
	DigestType	Digest;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货单位帐号类型
	BankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	BankAccountType	BankSecuAcc;
	///银行密码标志
	PwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	PwdFlagType	SecuPwdFlag;
	///交易柜员
	OperNoType	OperNo;
	///交易ID
	TIDType	TID;
	///用户标识
	UserIDType	UserID;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///银期销户信息
struct CancelAccountField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///性别
	GenderType	Gender;
	///国家代码
	CountryCodeType	CountryCode;
	///客户类型
	CustTypeType	CustType;
	///地址
	AddressType	Address;
	///邮编
	ZipCodeType	ZipCode;
	///电话号码
	TelephoneType	Telephone;
	///手机
	MobilePhoneType	MobilePhone;
	///传真
	FaxType	Fax;
	///电子邮件
	EMailType	EMail;
	///资金账户状态
	MoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///安装编号
	InstallIDType	InstallID;
	///验证客户证件号码标志
	YesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	CurrencyIDType	CurrencyID;
	///汇钞标志
	CashExchangeCodeType	CashExchangeCode;
	///摘要
	DigestType	Digest;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///渠道标志
	DeviceIDType	DeviceID;
	///期货单位帐号类型
	BankAccTypeType	BankSecuAccType;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///期货单位帐号
	BankAccountType	BankSecuAcc;
	///银行密码标志
	PwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	PwdFlagType	SecuPwdFlag;
	///交易柜员
	OperNoType	OperNo;
	///交易ID
	TIDType	TID;
	///用户标识
	UserIDType	UserID;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///银期变更银行账号信息
struct ChangeAccountField
{
	///业务功能码
	TradeCodeType	TradeCode;
	///银行代码
	BankIDType	BankID;
	///银行分支机构代码
	BankBrchIDType	BankBranchID;
	///期商代码
	BrokerIDType	BrokerID;
	///期商分支机构代码
	FutureBranchIDType	BrokerBranchID;
	///交易日期
	TradeDateType	TradeDate;
	///交易时间
	TradeTimeType	TradeTime;
	///银行流水号
	BankSerialType	BankSerial;
	///交易系统日期 
	TradeDateType	TradingDay;
	///银期平台消息流水号
	SerialType	PlateSerial;
	///最后分片标志
	LastFragmentType	LastFragment;
	///会话号
	SessionIDType	SessionID;
	///客户姓名
	IndividualNameType	CustomerName;
	///证件类型
	IdCardTypeType	IdCardType;
	///证件号码
	IdentifiedCardNoType	IdentifiedCardNo;
	///性别
	GenderType	Gender;
	///国家代码
	CountryCodeType	CountryCode;
	///客户类型
	CustTypeType	CustType;
	///地址
	AddressType	Address;
	///邮编
	ZipCodeType	ZipCode;
	///电话号码
	TelephoneType	Telephone;
	///手机
	MobilePhoneType	MobilePhone;
	///传真
	FaxType	Fax;
	///电子邮件
	EMailType	EMail;
	///资金账户状态
	MoneyAccountStatusType	MoneyAccountStatus;
	///银行帐号
	BankAccountType	BankAccount;
	///银行密码
	PasswordType	BankPassWord;
	///新银行帐号
	BankAccountType	NewBankAccount;
	///新银行密码
	PasswordType	NewBankPassWord;
	///投资者帐号
	AccountIDType	AccountID;
	///期货密码
	PasswordType	Password;
	///银行帐号类型
	BankAccTypeType	BankAccType;
	///安装编号
	InstallIDType	InstallID;
	///验证客户证件号码标志
	YesNoIndicatorType	VerifyCertNoFlag;
	///币种代码
	CurrencyIDType	CurrencyID;
	///期货公司银行编码
	BankCodingForFutureType	BrokerIDByBank;
	///银行密码标志
	PwdFlagType	BankPwdFlag;
	///期货资金密码核对标志
	PwdFlagType	SecuPwdFlag;
	///交易ID
	TIDType	TID;
	///摘要
	DigestType	Digest;
	///错误代码
	ErrorIDType	ErrorID;
	///错误信息
	ErrorMsgType	ErrorMsg;
};

///二级代理操作员银期权限
struct SecAgentACIDMapField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///资金账户
	AccountIDType	AccountID;
	///币种
	CurrencyIDType	CurrencyID;
	///境外中介机构资金帐号
	AccountIDType	BrokerSecAgentID;
};

///二级代理操作员银期权限查询
struct QrySecAgentACIDMapField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///资金账户
	AccountIDType	AccountID;
	///币种
	CurrencyIDType	CurrencyID;
};

///灾备中心交易权限
struct UserRightsAssignField
{
	///应用单元代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///交易中心代码
	DRIdentityIDType	DRIdentityID;
};

///经济公司是否有在本标示的交易权限
struct BrokerUserRightAssignField
{
	///应用单元代码
	BrokerIDType	BrokerID;
	///交易中心代码
	DRIdentityIDType	DRIdentityID;
	///能否交易
	BoolType	Tradeable;
};

///灾备交易转换报文
struct DRTransferField
{
	///原交易中心代码
	DRIdentityIDType	OrigDRIdentityID;
	///目标交易中心代码
	DRIdentityIDType	DestDRIdentityID;
	///原应用单元代码
	BrokerIDType	OrigBrokerID;
	///目标易用单元代码
	BrokerIDType	DestBrokerID;
};

///Fens用户信息
struct FensUserInfoField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///登录模式
	LoginModeType	LoginMode;
};

///当前银期所属交易中心
struct CurrTransferIdentityField
{
	///交易中心代码
	DRIdentityIDType	IdentityID;
};

///禁止登录用户
struct LoginForbiddenUserField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
	///IP地址
	IPAddressType	IPAddress;
};

///查询禁止登录用户
struct QryLoginForbiddenUserField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///用户代码
	UserIDType	UserID;
};

///UDP组播组信息
struct MulticastGroupInfoField
{
	///组播组IP地址
	IPAddressType	GroupIP;
	///组播组IP端口
	IPPortType	GroupPort;
	///源地址
	IPAddressType	SourceIP;
};

///资金账户基本准备金
struct TradingAccountReserveField
{
	///经纪公司代码
	BrokerIDType	BrokerID;
	///投资者帐号
	AccountIDType	AccountID;
	///基本准备金
	MoneyType	Reserve;
	///币种代码
	CurrencyIDType	CurrencyID;
};



#endif
