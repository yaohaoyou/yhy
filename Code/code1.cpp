#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

// 解析一行数据（支持逗号或空格分隔）
vector<string> splitLine(const string& line) {
    vector<string> tokens;
    string token;
    bool inQuotes = false;
    
    for (char c : line) {
        if (c == '"') {
            inQuotes = !inQuotes;
        } else if ((c == ',' || c == ' ') && !inQuotes) {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        } else if (c != '\r') {
            token += c;
        }
    }
    if (!token.empty()) {
        tokens.push_back(token);
    }
    return tokens;
}

// 安全转换字符串到 double（处理 NA 等情况）
double safeStod(const string& s) {
    if (s == "NA" || s.empty()) return 0.0;
    try {
        return stod(s);
    } catch (...) {
        return 0.0;
    }
}

// 安全转换字符串到 long long
long long safeStoll(const string& s) {
    if (s == "NA" || s.empty()) return 0;
    try {
        return stoll(s);
    } catch (...) {
        return 0;
    }
}

// 股票行情数据结构
struct StockData {
    string date;
    string code;
    double open;
    double high;
    double low;
    double close;
    long long volume;
    double amount;
    double amplitude;
    double pct_chg;
    double change;
    double turnover;
    
    // 用于存储前一日的数据（用于计算变化）
    double prev_close;
};

// 股票历史数据（用于计算技术指标）
struct StockHistory {
    string code;
    vector<double> closes;      // 收盘价历史
    vector<double> highs;       // 最高价历史
    vector<double> lows;        // 最低价历史
    vector<double> volumes;     // 成交量历史
    vector<double> pct_chgs;    // 涨跌幅历史
    double ma5, ma10, ma20;     // 移动平均线
    double ema12, ema26;        // 指数移动平均线（用于MACD）
    double prevEma12, prevEma26; // 前一日EMA值
    double momentum;             // 动量指标
    double volatility;           // 波动率
    double rsi;                  // RSI指标
    double macd, signal, histogram; // MACD指标
    double upper_band, lower_band, middle_band; // 布林带
    double atr;                  // 平均真实波幅
    double volume_ratio;         // 成交量比率
    double price_position;      // 价格在布林带中的位置（0-1）
    
    StockHistory() : code(""), ma5(0), ma10(0), ma20(0),
                     ema12(0), ema26(0), prevEma12(0), prevEma26(0),
                     momentum(0), volatility(0), rsi(50),
                     macd(0), signal(0), histogram(0),
                     upper_band(0), lower_band(0), middle_band(0),
                     atr(0), volume_ratio(1.0), price_position(0.5) {}
    
    StockHistory(const string& c) : code(c), ma5(0), ma10(0), ma20(0),
                                     ema12(0), ema26(0), prevEma12(0), prevEma26(0),
                                     momentum(0), volatility(0), rsi(50),
                                     macd(0), signal(0), histogram(0),
                                     upper_band(0), lower_band(0), middle_band(0),
                                     atr(0), volume_ratio(1.0), price_position(0.5) {}
    
    // 计算EMA（指数移动平均）
    double calculateEMA(const vector<double>& prices, int period, double prevEMA = 0) {
        if (prices.size() < period) return 0;
        if (prevEMA == 0) {
            // 首次计算，使用简单平均
            double sum = 0;
            for (int i = prices.size() - period; i < prices.size(); i++) {
                sum += prices[i];
            }
            return sum / period;
        }
        // EMA = (价格 - 前一日EMA) * 平滑系数 + 前一日EMA
        double multiplier = 2.0 / (period + 1.0);
        return (prices.back() - prevEMA) * multiplier + prevEMA;
    }
    
    // 更新技术指标
    void updateIndicators() {
        if (closes.size() < 2) return;
        
        // 计算移动平均线
        if (closes.size() >= 5) {
            double sum = 0;
            for (int i = closes.size() - 5; i < closes.size(); i++) {
                sum += closes[i];
            }
            ma5 = sum / 5.0;
        }
        if (closes.size() >= 10) {
            double sum = 0;
            for (int i = closes.size() - 10; i < closes.size(); i++) {
                sum += closes[i];
            }
            ma10 = sum / 10.0;
        }
        if (closes.size() >= 20) {
            double sum = 0;
            for (int i = closes.size() - 20; i < closes.size(); i++) {
                sum += closes[i];
            }
            ma20 = sum / 20.0;
            middle_band = ma20;  // 布林带中轨
        }
        
        // 计算EMA
        if (closes.size() >= 12) {
            ema12 = calculateEMA(closes, 12, prevEma12);
            prevEma12 = ema12;
        }
        if (closes.size() >= 26) {
            ema26 = calculateEMA(closes, 26, prevEma26);
            prevEma26 = ema26;
        }
        
        // 计算MACD
        static map<string, double> signalHistory;  // 每只股票独立的signal历史
        if (ema12 > 0 && ema26 > 0) {
            macd = ema12 - ema26;
            // Signal线是MACD的9日EMA（简化版）
            if (signalHistory.find(code) == signalHistory.end()) {
                signalHistory[code] = macd;
            }
            double prevSignal = signalHistory[code];
            signal = macd * 0.2 + prevSignal * 0.8;  // 简化版signal（9日EMA的近似）
            signalHistory[code] = signal;
            histogram = macd - signal;
        }
        
        // 计算动量（最近5日收益率）
        if (closes.size() >= 6) {
            momentum = (closes.back() - closes[closes.size() - 6]) / closes[closes.size() - 6] * 100.0;
        }
        
        // 计算波动率和布林带
        if (closes.size() >= 20) {
            double mean = ma20;
            double variance = 0;
            for (int i = closes.size() - 20; i < closes.size(); i++) {
                variance += (closes[i] - mean) * (closes[i] - mean);
            }
            double std_dev = sqrt(variance / 20.0);
            volatility = std_dev / mean * 100.0;
            
            // 布林带：中轨±2倍标准差
            upper_band = mean + 2.0 * std_dev;
            lower_band = mean - 2.0 * std_dev;
            
            // 价格在布林带中的位置
            if (upper_band > lower_band) {
                price_position = (closes.back() - lower_band) / (upper_band - lower_band);
                price_position = max(0.0, min(1.0, price_position));
            }
        }
        
        // 计算ATR（平均真实波幅）
        if (highs.size() >= 14 && lows.size() >= 14 && closes.size() >= 15) {
            double sum_tr = 0;
            int startIdx = closes.size() - 14;
            for (int i = startIdx; i < closes.size(); i++) {
                double tr1 = highs[i] - lows[i];
                double prevClose = (i > 0) ? closes[i-1] : closes[i];
                double tr2 = fabs(highs[i] - prevClose);
                double tr3 = fabs(lows[i] - prevClose);
                sum_tr += max(tr1, max(tr2, tr3));
            }
            atr = sum_tr / 14.0;
        }
        
        // 计算成交量比率
        if (volumes.size() >= 10) {
            double avgVol = 0;
            for (int i = volumes.size() - 10; i < volumes.size() - 1; i++) {
                avgVol += volumes[i];
            }
            avgVol /= 9.0;
            if (avgVol > 0) {
                volume_ratio = volumes.back() / avgVol;
            }
        }
        
        // 改进的RSI计算
        if (pct_chgs.size() >= 14) {
            double gain = 0, loss = 0;
            for (int i = pct_chgs.size() - 14; i < pct_chgs.size(); i++) {
                if (pct_chgs[i] > 0) gain += pct_chgs[i];
                else loss += fabs(pct_chgs[i]);
            }
            if (loss > 0) {
                double rs = gain / loss;
                rsi = 100.0 - (100.0 / (1.0 + rs));
            } else if (gain > 0) {
                rsi = 100.0;
            } else {
                rsi = 50.0;
            }
        }
    }
};

// 账户状态
struct Account {
    double cash;  // 现金余额
    map<string, int> holdings;  // 持仓：股票代码 -> 股数
    
    Account() : cash(0.0) {}
};

// 交易参数
struct TradingParams {
    int n;           // 股票数量
    int D;           // 交易日总数
    double m;        // 初始现金
    int L;           // 最小交易单位（1手）
    double alpha;    // 手续费率
    double com_min;  // 最低佣金
    double beta;     // 印花税率
    int K_max;       // 单日委托上限
};

// 四舍五入到分（两位小数）
double roundToCent(double value) {
    return round(value * 100.0) / 100.0;
}

// 计算买入费用
double calculateBuyCost(double price, int qty, const TradingParams& params) {
    double V = price * qty;
    double commission = max(params.com_min, params.alpha * V);
    return roundToCent(V + commission);
}

// 计算卖出收入
double calculateSellIncome(double price, int qty, const TradingParams& params) {
    double V = price * qty;
    double stamp_tax = params.beta * V;
    double commission = max(params.com_min, params.alpha * V);
    return roundToCent(V - stamp_tax - commission);
}

// 读取一行行情数据（支持逗号或空格分隔）
StockData readStockData() {
    string line;
    getline(cin, line);
    
    vector<string> tokens = splitLine(line);
    StockData stock;
    
    if (tokens.size() >= 12) {
        stock.date = tokens[0];
        stock.code = tokens[1];
        stock.open = safeStod(tokens[2]);
        stock.high = safeStod(tokens[3]);
        stock.low = safeStod(tokens[4]);
        stock.close = safeStod(tokens[5]);
        stock.volume = safeStoll(tokens[6]);
        stock.amount = safeStod(tokens[7]);
        stock.amplitude = safeStod(tokens[8]);
        stock.pct_chg = safeStod(tokens[9]);
        stock.change = safeStod(tokens[10]);
        stock.turnover = safeStod(tokens[11]);
    }
    
    return stock;
}

// 订单结构
struct Order {
    string type;  // "BUY" 或 "SELL"
    string code;  // 股票代码
    int qty;      // 数量
    
    Order(const string& t, const string& c, int q) : type(t), code(c), qty(q) {}
};

// 持仓成本记录（用于计算盈亏）
struct Position {
    string code;
    int qty;
    double avgCost;  // 平均成本价
    
    Position(const string& c, int q, double cost) : code(c), qty(q), avgCost(cost) {}
};

// 多因子评分系统
struct StockScore {
    string code;
    double score;
    double currentPrice;
    
    StockScore(const string& c, double s, double p) : code(c), score(s), currentPrice(p) {}
    
    bool operator<(const StockScore& other) const {
        return score > other.score;  // 降序排列
    }
};

// 市场情绪分析
struct MarketSentiment {
    double avgPctChg;        // 平均涨跌幅
    double risingRatio;      // 上涨股票比例
    double avgVolumeRatio;   // 平均成交量比率
    double marketStrength;   // 市场强度（0-100）
    bool isBullish;          // 是否看涨
    bool isBearish;          // 是否看跌
    
    MarketSentiment() : avgPctChg(0), risingRatio(0), avgVolumeRatio(1.0),
                       marketStrength(50), isBullish(false), isBearish(false) {}
};

// 计算市场情绪
MarketSentiment analyzeMarket(const vector<StockData>& data, 
                              const map<string, StockHistory>& histories) {
    MarketSentiment sentiment;
    if (data.empty()) return sentiment;
    
    double totalPctChg = 0;
    int risingCount = 0;
    int validCount = 0;
    double totalVolRatio = 0;
    
    for (const auto& stock : data) {
        if (stock.open == 0) continue;  // 跳过停牌
        
        validCount++;
        totalPctChg += stock.pct_chg;
        if (stock.pct_chg > 0) risingCount++;
        
        auto it = histories.find(stock.code);
        if (it != histories.end() && it->second.volume_ratio > 0) {
            totalVolRatio += it->second.volume_ratio;
        }
    }
    
    if (validCount > 0) {
        sentiment.avgPctChg = totalPctChg / validCount;
        sentiment.risingRatio = (double)risingCount / validCount;
        sentiment.avgVolumeRatio = totalVolRatio / validCount;
        
        // 计算市场强度
        sentiment.marketStrength = 50.0;
        sentiment.marketStrength += sentiment.avgPctChg * 5.0;  // 涨跌幅影响
        sentiment.marketStrength += (sentiment.risingRatio - 0.5) * 30.0;  // 上涨比例影响
        sentiment.marketStrength += (sentiment.avgVolumeRatio - 1.0) * 10.0;  // 成交量影响
        sentiment.marketStrength = max(0.0, min(100.0, sentiment.marketStrength));
        
        sentiment.isBullish = sentiment.marketStrength > 60;
        sentiment.isBearish = sentiment.marketStrength < 40;
    }
    
    return sentiment;
}

// 改进的交易策略：多因子模型 + 风险管理 + 市场情绪
vector<Order> generateOrders(
    const vector<StockData>& prevDayData,
    const Account& account,
    const TradingParams& params,
    map<string, StockHistory>& stockHistories,
    map<string, double>& positionCosts) {
    
    vector<Order> orders;
    
    // 更新所有股票的历史数据和技术指标
    for (const auto& stock : prevDayData) {
        if (stock.open == 0) continue;  // 跳过停牌股票
        
        if (stockHistories.find(stock.code) == stockHistories.end()) {
            stockHistories[stock.code] = StockHistory(stock.code);
        }
        
        auto& history = stockHistories[stock.code];
        history.closes.push_back(stock.close);
        history.highs.push_back(stock.high);
        history.lows.push_back(stock.low);
        history.volumes.push_back(stock.volume);
        history.pct_chgs.push_back(stock.pct_chg);
        
        // 限制历史数据长度（保留最近30天）
        if (history.closes.size() > 30) {
            history.closes.erase(history.closes.begin());
            history.highs.erase(history.highs.begin());
            history.lows.erase(history.lows.begin());
            history.volumes.erase(history.volumes.begin());
            history.pct_chgs.erase(history.pct_chgs.begin());
        }
        
        history.updateIndicators();
    }
    
    // ========== 市场情绪分析 ==========
    MarketSentiment market = analyzeMarket(prevDayData, stockHistories);
    
    // 根据市场情绪调整策略参数
    double marketAdjustment = 1.0;
    if (market.isBearish) {
        marketAdjustment = 0.7;  // 熊市减少买入
    } else if (market.isBullish) {
        marketAdjustment = 1.2;  // 牛市增加买入
    }
    
    // ========== 买入策略：多因子评分 ==========
    vector<StockScore> buyCandidates;
    
    for (const auto& stock : prevDayData) {
        if (stock.open == 0) continue;  // 跳过停牌
        
        auto it = stockHistories.find(stock.code);
        if (it == stockHistories.end()) continue;
        const auto& history = it->second;
        
        if (history.closes.size() < 5) continue;  // 需要足够的历史数据
        
        double score = 0.0;
        bool validCandidate = true;
        
        // ========== 基础筛选条件 ==========
        // 必须条件：避免涨停（无法买入）
        if (stock.pct_chg >= 9.5) {
            validCandidate = false;
        }
        
        // 必须条件：价格不能为0
        if (stock.close <= 0) {
            validCandidate = false;
        }
        
        if (!validCandidate) continue;
        
        // ========== 多因子评分系统 ==========
        
        // 因子1：趋势因子（均线多头排列）- 权重最高
        if (history.ma5 > 0 && history.ma10 > 0 && history.ma20 > 0) {
            if (stock.close > history.ma5 && history.ma5 > history.ma10 && history.ma10 > history.ma20) {
                score += 25.0;  // 强势多头趋势
            } else if (stock.close > history.ma5 && history.ma5 > history.ma10) {
                score += 15.0;  // 短期多头
            } else if (stock.close > history.ma20) {
                score += 8.0;   // 在长期均线之上
            } else {
                score -= 10.0;  // 在均线下方，趋势较弱
            }
        }
        
        // 因子2：MACD因子（趋势确认）
        if (history.macd > 0 && history.histogram > 0) {
            score += 12.0;  // MACD金叉且柱状图为正
        } else if (history.macd > history.signal) {
            score += 6.0;   // MACD在signal线上方
        } else if (history.histogram < -0.5) {
            score -= 8.0;   // MACD死叉
        }
        
        // 因子3：动量因子（价格动量）
        if (history.momentum > 8.0) {
            score += min(18.0, history.momentum * 1.5);  // 强动量
        } else if (history.momentum > 3.0) {
            score += history.momentum * 1.2;  // 中等动量
        } else if (history.momentum < -8.0) {
            score -= 15.0;  // 负动量严重惩罚
        } else if (history.momentum < -3.0) {
            score -= 8.0;   // 负动量惩罚
        }
        
        // 因子4：涨跌幅因子（适度上涨最佳）
        if (stock.pct_chg > 0 && stock.pct_chg < 5.0) {
            score += min(15.0, stock.pct_chg * 3.0);  // 适度上涨
        } else if (stock.pct_chg >= 5.0 && stock.pct_chg < 9.5) {
            score += 10.0;  // 大涨但未涨停
        } else if (stock.pct_chg < -3.0) {
            score -= 12.0;  // 大跌惩罚
        }
        
        // 因子5：成交量因子（放量上涨）
        if (history.volume_ratio > 2.0) {
            score += 15.0;  // 显著放量
        } else if (history.volume_ratio > 1.5) {
            score += 10.0;  // 明显放量
        } else if (history.volume_ratio > 1.2) {
            score += 6.0;   // 温和放量
        } else if (history.volume_ratio < 0.7) {
            score -= 8.0;   // 缩量
        }
        
        // 因子6：换手率因子（适度活跃）
        if (stock.turnover > 2.0 && stock.turnover < 12.0) {
            score += min(12.0, stock.turnover * 0.8);  // 适度活跃
        } else if (stock.turnover > 15.0) {
            score -= 8.0;  // 过度活跃可能有问题
        } else if (stock.turnover < 0.5) {
            score -= 5.0;  // 流动性不足
        }
        
        // 因子7：RSI因子（避免超买，寻找超卖反弹）
        if (history.rsi > 0) {
            if (history.rsi > 25 && history.rsi < 65) {
                score += 8.0;  // 健康区间
            } else if (history.rsi < 25) {
                score += 12.0;  // 超卖，反弹机会
            } else if (history.rsi > 75) {
                score -= 18.0;  // 严重超买
            } else if (history.rsi > 65) {
                score -= 8.0;   // 接近超买
            }
        }
        
        // 因子8：布林带因子（价格位置）
        if (history.upper_band > history.lower_band) {
            if (history.price_position > 0.2 && history.price_position < 0.8) {
                score += 10.0;  // 价格在中轨附近，有上涨空间
            } else if (history.price_position < 0.2) {
                score += 15.0;  // 价格接近下轨，反弹机会
            } else if (history.price_position > 0.9) {
                score -= 12.0;  // 价格接近上轨，可能回调
            }
        }
        
        // 因子9：波动率因子（适中波动最佳）
        if (history.volatility > 0) {
            if (history.volatility > 2.5 && history.volatility < 7.0) {
                score += 8.0;  // 适度波动，有交易机会
            } else if (history.volatility > 12.0) {
                score -= 12.0;  // 过度波动，风险高
            } else if (history.volatility < 1.5) {
                score -= 5.0;   // 波动太小，缺乏机会
            }
        }
        
        // 因子10：ATR因子（真实波幅）
        if (history.atr > 0 && stock.close > 0) {
            double atr_pct = history.atr / stock.close * 100.0;
            if (atr_pct > 2.0 && atr_pct < 6.0) {
                score += 6.0;  // 适度的真实波幅
            } else if (atr_pct > 8.0) {
                score -= 8.0;  // 波幅过大
            }
        }
        
        // 因子11：振幅因子（有上涨空间）
        if (stock.amplitude > 4.0 && stock.amplitude < 9.0) {
            score += 8.0;  // 适度振幅
        } else if (stock.amplitude > 10.0) {
            score -= 5.0;  // 振幅过大
        }
        
        // 因子12：价格相对位置（相对强度）
        if (history.closes.size() >= 20) {
            double maxPrice = *max_element(history.closes.end() - 20, history.closes.end());
            double minPrice = *min_element(history.closes.end() - 20, history.closes.end());
            if (maxPrice > minPrice) {
                double pricePos = (stock.close - minPrice) / (maxPrice - minPrice);
                if (pricePos > 0.3 && pricePos < 0.8) {
                    score += 6.0;  // 价格在合理区间
                } else if (pricePos < 0.2) {
                    score += 8.0;  // 价格在低位，有上涨空间
                } else if (pricePos > 0.9) {
                    score -= 8.0;  // 价格在高位
                }
            }
        }
        
        // 因子13：市场情绪因子
        if (market.isBullish) {
            score += 8.0;  // 牛市加分
        } else if (market.isBearish) {
            score -= 10.0;  // 熊市减分
        }
        
        // 因子14：相对市场表现（跑赢大盘）
        if (stock.pct_chg > market.avgPctChg * 1.5) {
            score += 10.0;  // 显著跑赢市场
        } else if (stock.pct_chg > market.avgPctChg) {
            score += 5.0;   // 跑赢市场
        } else if (stock.pct_chg < market.avgPctChg * 0.5) {
            score -= 8.0;   // 跑输市场
        }
        
        // 根据市场情绪调整得分阈值
        double minScore = 40.0;
        if (market.isBearish) {
            minScore = 50.0;  // 熊市提高买入标准
        } else if (market.isBullish) {
            minScore = 35.0;  // 牛市降低买入标准
        }
        
        // 只考虑得分较高的股票
        if (score > minScore) {
            buyCandidates.push_back(StockScore(stock.code, score, stock.close));
        }
    }
    
    // 按得分排序，选择前N只
    sort(buyCandidates.begin(), buyCandidates.end());
    
    // 智能仓位分配：根据得分和市场情绪动态分配
    double cashRatio = 0.85;
    if (market.isBearish) {
        cashRatio = 0.70;  // 熊市保留更多现金
    } else if (market.isBullish) {
        cashRatio = 0.90;  // 牛市可以更激进
    }
    
    double availableCash = account.cash * cashRatio;
    int maxPositions = min(12, (int)buyCandidates.size());
    
    // 根据市场情绪调整最大持仓数
    if (market.isBearish) {
        maxPositions = min(8, maxPositions);  // 熊市减少持仓
    } else if (market.isBullish) {
        maxPositions = min(15, maxPositions);  // 牛市可以增加持仓
    }
    
    // 计算总得分用于归一化
    double totalScore = 0;
    for (int i = 0; i < min(maxPositions, (int)buyCandidates.size()); i++) {
        totalScore += buyCandidates[i].score;
    }
    
    for (int i = 0; i < maxPositions && orders.size() < params.K_max && availableCash > 5000; i++) {
        const auto& candidate = buyCandidates[i];
        
        // 检查是否已持有
        auto it = account.holdings.find(candidate.code);
        if (it != account.holdings.end() && it->second > 0) {
            continue;  // 已持有，跳过（避免重复买入）
        }
        
        // 根据得分和排名动态分配仓位
        // 排名越靠前，得分越高，分配越多资金
        double scoreWeight = candidate.score / max(1.0, totalScore);
        double rankWeight = 1.0 - (i * 0.05);  // 排名越靠后，权重递减
        double allocationRatio = min(0.15, max(0.08, scoreWeight * rankWeight * 2.0));
        
        double allocation = availableCash * allocationRatio;
        double price = candidate.currentPrice;
        
        // 确保最小买入金额
        if (allocation < 5000) allocation = 5000;
        
        int qty = (int)(allocation / price);
        qty = (qty / params.L) * params.L;  // 调整为L的倍数
        
        if (qty >= params.L) {
            double cost = calculateBuyCost(price, qty, params);
            if (cost <= availableCash) {
                orders.push_back(Order("BUY", candidate.code, qty));
                availableCash -= cost;
            }
        }
    }
    
    // ========== 卖出策略：止损止盈 + 趋势反转 ==========
    for (const auto& entry : account.holdings) {
        if (orders.size() >= params.K_max) break;
        
        const string& code = entry.first;
        int qty = entry.second;
        if (qty < params.L) continue;
        
        // 找到该股票的行情数据
        const StockData* stockPtr = nullptr;
        for (const auto& stock : prevDayData) {
            if (stock.code == code) {
                stockPtr = &stock;
                break;
            }
        }
        if (!stockPtr || stockPtr->open == 0) continue;
        
        const auto& stock = *stockPtr;
        auto it = stockHistories.find(code);
        if (it == stockHistories.end()) continue;
        const auto& history = it->second;
        
        // 获取持仓成本
        double avgCost = positionCosts[code];
        if (avgCost <= 0) avgCost = stock.close;  // 如果没有记录，使用当前价
        
        double currentPrice = stock.close;
        double profitPct = (currentPrice - avgCost) / avgCost * 100.0;
        
        bool shouldSell = false;
        int sellQty = 0;
        int sellPriority = 0;  // 卖出优先级，越高越紧急
        
        // ========== 卖出条件（按优先级排序）==========
        
        // 条件1：严格止损（亏损超过10%或ATR止损）
        double stopLoss = -10.0;
        if (history.atr > 0 && stock.close > 0) {
            // 动态止损：基于ATR，至少亏损超过2倍ATR
            double atrStopLoss = -2.0 * history.atr / stock.close * 100.0;
            stopLoss = max(-10.0, atrStopLoss);
        }
        
        if (profitPct < stopLoss) {
            shouldSell = true;
            sellQty = qty;  // 全部卖出止损
            sellPriority = 100;  // 最高优先级
        }
        // 条件2：中等止损（亏损超过6%）
        else if (profitPct < -6.0) {
            shouldSell = true;
            sellQty = min(qty, (qty * 2 / 3 / params.L) * params.L);  // 卖出2/3
            if (sellQty < params.L) sellQty = qty;
            sellPriority = 80;
        }
        // 条件3：大幅止盈（盈利超过20%）
        else if (profitPct > 20.0) {
            shouldSell = true;
            sellQty = min(qty, (qty * 3 / 4 / params.L) * params.L);  // 卖出3/4
            if (sellQty < params.L) sellQty = qty;
            sellPriority = 70;
        }
        // 条件4：中等止盈（盈利超过12%）
        else if (profitPct > 12.0) {
            shouldSell = true;
            sellQty = min(qty, (qty / 2 / params.L) * params.L);  // 卖出50%
            if (sellQty < params.L) sellQty = qty;
            sellPriority = 60;
        }
        // 条件5：趋势反转（跌破关键均线）
        else if (history.ma5 > 0 && history.ma10 > 0) {
            if (currentPrice < history.ma5 && history.ma5 < history.ma10 && profitPct > -2.0) {
                shouldSell = true;
                sellQty = min(qty, (qty / 2 / params.L) * params.L);  // 卖出50%
                if (sellQty < params.L) sellQty = qty;
                sellPriority = 50;
            }
        }
        // 条件6：MACD死叉
        else if (history.macd < history.signal && history.histogram < -0.3 && profitPct > -3.0) {
            shouldSell = true;
            sellQty = min(qty, (qty / 2 / params.L) * params.L);
            if (sellQty < params.L) sellQty = qty;
            sellPriority = 45;
        }
        // 条件7：大幅下跌（单日跌幅超过6%）
        else if (stock.pct_chg < -6.0) {
            shouldSell = true;
            sellQty = min(qty, (qty * 2 / 3 / params.L) * params.L);
            if (sellQty < params.L) sellQty = qty;
            sellPriority = 55;
        }
        // 条件8：中等下跌（单日跌幅超过4%且盈利不多）
        else if (stock.pct_chg < -4.0 && profitPct < 3.0) {
            shouldSell = true;
            sellQty = min(qty, (qty / 2 / params.L) * params.L);
            if (sellQty < params.L) sellQty = qty;
            sellPriority = 40;
        }
        // 条件9：RSI严重超买（>85）且盈利
        else if (history.rsi > 85 && profitPct > 8.0) {
            shouldSell = true;
            sellQty = min(qty, (qty / 2 / params.L) * params.L);
            if (sellQty < params.L) sellQty = qty;
            sellPriority = 35;
        }
        // 条件10：RSI超买（>75）且盈利较多
        else if (history.rsi > 75 && profitPct > 10.0) {
            shouldSell = true;
            sellQty = min(qty, (qty / 3 / params.L) * params.L);
            if (sellQty < params.L) sellQty = qty;
            sellPriority = 30;
        }
        // 条件11：价格突破布林带上轨且盈利
        else if (history.upper_band > 0 && currentPrice > history.upper_band * 1.02 && profitPct > 5.0) {
            shouldSell = true;
            sellQty = min(qty, (qty / 3 / params.L) * params.L);
            if (sellQty < params.L) sellQty = qty;
            sellPriority = 25;
        }
        // 条件12：成交量异常萎缩且盈利
        else if (history.volume_ratio < 0.5 && profitPct > 8.0) {
            shouldSell = true;
            sellQty = min(qty, (qty / 3 / params.L) * params.L);
            if (sellQty < params.L) sellQty = qty;
            sellPriority = 20;
        }
        // 条件13：连续下跌（最近3日累计跌幅>8%）
        else if (history.pct_chgs.size() >= 3) {
            double recentDecline = 0;
            for (int i = history.pct_chgs.size() - 3; i < history.pct_chgs.size(); i++) {
                recentDecline += history.pct_chgs[i];
            }
            if (recentDecline < -8.0 && profitPct < 2.0) {
                shouldSell = true;
                sellQty = min(qty, (qty / 2 / params.L) * params.L);
                if (sellQty < params.L) sellQty = qty;
                sellPriority = 40;
            }
        }
        
        if (shouldSell && sellQty >= params.L) {
            orders.push_back(Order("SELL", code, sellQty));
        }
    }
    
    return orders;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    TradingParams params;
    Account account;
    
    // 历史数据管理
    map<string, StockHistory> stockHistories;
    
    // 持仓成本跟踪（股票代码 -> 平均成本价）
    map<string, double> positionCosts;
    
    // 读取初始化参数
    string initLine;
    getline(cin, initLine);
    stringstream ss(initLine);
    
    string cmd;
    ss >> cmd;  // "INIT"
    ss >> params.n;
    ss >> params.D;
    ss >> params.m;
    ss >> params.L;
    ss >> params.alpha;
    ss >> params.com_min;
    ss >> params.beta;
    ss >> params.K_max;
    
    account.cash = params.m;
    
    // 读取基准日（day 0）行情
    vector<StockData> prevDayData(params.n);
    for (int i = 0; i < params.n; i++) {
        prevDayData[i] = readStockData();
        prevDayData[i].prev_close = prevDayData[i].close;
        account.holdings[prevDayData[i].code] = 0;  // 初始化持仓为0
        
        // 初始化历史数据
        stockHistories[prevDayData[i].code] = StockHistory(prevDayData[i].code);
        stockHistories[prevDayData[i].code].closes.push_back(prevDayData[i].close);
        stockHistories[prevDayData[i].code].highs.push_back(prevDayData[i].high);
        stockHistories[prevDayData[i].code].lows.push_back(prevDayData[i].low);
        stockHistories[prevDayData[i].code].volumes.push_back(prevDayData[i].volume);
        stockHistories[prevDayData[i].code].pct_chgs.push_back(prevDayData[i].pct_chg);
    }
    
    // 主循环：处理每个交易日
    for (int day = 1; day <= params.D; day++) {
        // 基于前一天的数据生成委托
        // 注意：account和positionCosts是基于预估的，因为Judge会实际执行委托
        // 我们无法准确知道执行后的真实状态，但可以基于历史委托进行估算
        vector<Order> orders = generateOrders(prevDayData, account, params, stockHistories, positionCosts);
        
        // 输出委托（限制在 K_max 以内）
        int orderCount = min((int)orders.size(), params.K_max);
        for (int i = 0; i < orderCount; i++) {
            cout << orders[i].type << " " << orders[i].code << " " << orders[i].qty << "\n";
        }
        
        // 输出 DONE 并 flush
        cout << "DONE\n";
        cout.flush();
        
        // 预估更新持仓和成本（用于后续策略决策，虽然不够准确）
        // 实际执行由Judge完成，我们只能估算
        for (const auto& order : orders) {
            if (order.type == "BUY") {
                // 预估买入成本（使用前一天收盘价，实际是开盘价执行）
                double price = 0;
                for (const auto& stock : prevDayData) {
                    if (stock.code == order.code) {
                        price = stock.close;  // 使用前一天收盘价预估（实际是当天开盘价）
                        break;
                    }
                }
                if (price > 0) {
                    // 更新平均成本（预估）
                    int oldQty = account.holdings[order.code];
                    double oldCost = positionCosts[order.code];
                    if (oldCost <= 0) oldCost = price;
                    
                    int newQty = oldQty + order.qty;
                    double newCost = (oldQty * oldCost + order.qty * price) / newQty;
                    positionCosts[order.code] = newCost;
                    account.holdings[order.code] = newQty;
                    
                    // 预估现金减少（实际由Judge计算）
                    double cost = calculateBuyCost(price, order.qty, params);
                    account.cash = max(0.0, account.cash - cost);
                }
            } else if (order.type == "SELL") {
                // 卖出减少持仓
                int oldQty = account.holdings[order.code];
                if (oldQty >= order.qty) {
                    account.holdings[order.code] -= order.qty;
                    
                    // 预估现金增加
                    double price = 0;
                    for (const auto& stock : prevDayData) {
                        if (stock.code == order.code) {
                            price = stock.close;
                            break;
                        }
                    }
                    if (price > 0) {
                        double income = calculateSellIncome(price, order.qty, params);
                        account.cash += income;
                    }
                    
                    // 如果全部卖出，清除成本记录
                    if (account.holdings[order.code] <= 0) {
                        account.holdings[order.code] = 0;
                        // 保留成本记录用于参考，不清除
                    }
                }
            }
        }
        
        // 读取当天的行情数据
        for (int i = 0; i < params.n; i++) {
            StockData newData = readStockData();
            
            // 更新 prev_close（使用前一天的收盘价）
            for (auto& stock : prevDayData) {
                if (stock.code == newData.code) {
                    newData.prev_close = stock.close;  // 保存前一天的收盘价
                    stock = newData;
                    break;
                }
            }
        }
        
        // 注意：实际账户状态（现金、持仓）由Judge维护和执行
        // 这里的预估可能不够准确，但可以用于策略参考
        // 更精确的方法需要根据Judge返回的执行结果来更新，但题目中没有提供这个接口
    }
    
    // 最后一天收盘后可以再提交一次委托
    vector<Order> finalOrders = generateOrders(prevDayData, account, params, stockHistories, positionCosts);
    int orderCount = min((int)finalOrders.size(), params.K_max);
    for (int i = 0; i < orderCount; i++) {
        cout << finalOrders[i].type << " " << finalOrders[i].code << " " << finalOrders[i].qty << "\n";
    }
    cout << "DONE\n";
    cout.flush();
    
    // 等待 FINISH 消息
    string finishLine;
    getline(cin, finishLine);
    
    return 0;
}

