#5개의 모델을 찾기. 변화율이 가장 작은 5개의 모델을 찾는 방법.
#cv_diff_rate를 이용해서 각 그룹의 절대값 cv_diff_rate에 대한 합이 가장 낮은 주식 5개 정하기.
import pandas as pd


def sum_of_abs_cv_diff_rate(Dataframe):

    cv_rate_series=abs(Dataframe["cv_diff_rate"])
    return cv_rate_series.sum()


def find_stable_rate_stocks(stocks, n=15):

    n_stocks = dict()
    while n > 0:
        stock_name = min(stocks, key=stocks.get)
        n_stocks[stock_name]=stocks[stock_name]
        del stocks[stock_name]
        n -= 1
    return n_stocks


if __name__ == "__main__":
    df = pd.read_csv("stock_history_add.csv", encoding="euc-kr")

    stock_dict=dict() #key:주식이름, value=sum(abs())

    for name, group in df.groupby("stockname"):

        group = group.copy() #SettingWithCopyWarning 방지
        if len(group.index) > 100:
            stock_dict[name]=sum_of_abs_cv_diff_rate(group)

    stocks=find_stable_rate_stocks(stock_dict)
    for key in stocks:
        print(key, stocks[key])



