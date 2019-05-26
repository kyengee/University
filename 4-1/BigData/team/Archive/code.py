import pandas as pd

#stock_history_add file을 만들기 위함 .py

#1.cv_diff_value
def make_cv_diff_value(Dataframe):

    i=Dataframe.index[-1]
    k = Dataframe.index[0]
    while i > k:
        Dataframe.loc[i-1, "cv_diff_value"] = (Dataframe.loc[i-1, "close_value"] - Dataframe.loc[i, "close_value"])
        i -= 1

    return Dataframe["cv_diff_value"]

#2.cv_diff_rate
def make_cv_diff_rate(Dataframe):

    close_value_Series = Dataframe["close_value"]
    cv_diff_rate_Series = Dataframe["cv_diff_rate"]
    last_index = close_value_Series.index[-1]

    for index in Dataframe.index:
        if index == last_index: break
        cv_diff_rate_Series.at[index] = close_value_Series.at[index] / close_value_Series.at[index + 1] * 100 - 100
    return cv_diff_rate_Series

#3.cv_maN_value
def make_cv_maN_value(Dataframe,n=5): #parameter filename=".csv file", n=number,default=5
    if len(Dataframe) < n: return
    #주가이동평균선은 시장의 전반적인 주가 흐름을 판단하고 향후 주가의 추이를 전망하는 데 자주 사용되는 주식시장의 대표적인 기술지표

    g_close=Dataframe["close_value"]
    #cv_ma_value=g_close.rolling(window=n).mean().shift(-(n-1)) #Series type
    Dataframe["cv_maN_value"] = g_close.rolling(window=n).mean().shift(-(n - 1))  # Series type

    return Dataframe["cv_maN_value"]

#4.cv_maN_rate
def make_cv_maN_rate(Dataframe,n=5):
    if len(Dataframe) < n: return
    g_close = Dataframe["close_value"]
    cv_ma_value = g_close.rolling(window=n).mean().shift(-(n - 1))  # Series type

    i=Dataframe.index[-n]
    k = Dataframe.index[0]

    while i > k:
            Dataframe.loc[i-1,"cv_ma"+ str(n) +"_rate"] = (cv_ma_value[i-1]-cv_ma_value[i])/cv_ma_value[i]*100 #rolling 함수 쓰기.
            i -= 1

    return Dataframe["cv_ma"+ str(n) +"_rate"]

#5.ud_Nd
def make_ud_Nd(Dataframe,N=5):
    if len(Dataframe) < N: return
    close_value_Series = Dataframe["close_value"]
    ud_Nd_Series = Dataframe["ud_" + str(N) + "d"]
    last_index = close_value_Series.index[-N]

    for index in Dataframe.index:
        if index == last_index: break
        val = 0
        for i in range(0, N, 1):
            if close_value_Series.at[index + i] - close_value_Series.at[index + i + 1] > 0:
                val += 1
            else:
                val -= 1

        if val % N == 0:
            val = val / N
        else:
            val = 0
        ud_Nd_Series.at[index + 1] = val
    return ud_Nd_Series

#6.cvNd_diff_rate
def make_cvNd_diff_rate(Dataframe, N=5):
    if len(Dataframe) < N: return
    close_value_Series = Dataframe["close_value"]
    cvNd_diff_rate_Series = Dataframe["cv" + str(N) + "d_diff_rate"]
    last_index = close_value_Series.index[-N]

    for index in Dataframe.index:
        if index == last_index: break
        cvNd_diff_rate_Series.at[index + 1] = (close_value_Series.at[index] - close_value_Series.at[index + N]) / close_value_Series.at[index + N]
    return cvNd_diff_rate_Series


if __name__ == "__main__":
    # 추가할 컬럼스를 리스트화 시킴
    add_columns=["basic_date", "stockname", "stock_code", "open_value","high_value", "low_value", "close_value", "volume_value",
                 "cv_diff_value", "cv_diff_rate", "cv_ma3_value","cv_ma4_value", "cv_ma5_value", "cv_ma3_rate", "cv_ma4_rate", "cv_ma5_rate",
                 "ud_3d", "ud_4d", "ud_5d", "cv3d_diff_rate", "cv4d_diff_rate", "cv5d_diff_rate"]

    # csv파일을 읽어 컬럼 리스트 수정.
    df = pd.read_csv("stock_history.csv", skiprows=[0], names=add_columns, encoding='euc-kr') #추가할 컬럼을 넣어 read file.

    # 함수가 돌아갈때마다 생기는 각 그룹의 결과값을 저장하기 위한 리스트 모음
    lst_cv_diff_value=[]
    lst_cv_diff_rate=[]
    lst_cv_ma3_value, lst_cv_ma4_value, lst_cv_ma5_value=[], [], []
    lst_cv_ma3_rate, lst_cv_ma4_rate, lst_cv_ma5_rate=[], [], []
    lst_ud_3d, lst_ud_4d, lst_ud_5d=[], [], []
    lst_cv3d_diff_rate, lst_cv4d_diff_rate, lst_cv5d_diff_rate=[], [], []

    for name, group in df.groupby("stockname"):
        group = group.copy() #SettingWithCopyWarning 방지


        #리스트에 각 그룹마다의 결과값을 append함수로 넣기.

        lst_cv_diff_value.append(make_cv_diff_value(group))

        lst_cv_diff_rate.append(make_cv_diff_rate(group))

        lst_cv_ma3_value.append(make_cv_maN_value(group, 3))
        lst_cv_ma4_value.append(make_cv_maN_value(group, 4))
        lst_cv_ma5_value.append(make_cv_maN_value(group))

        lst_cv_ma3_rate.append(make_cv_maN_rate(group, 3))
        lst_cv_ma4_rate.append(make_cv_maN_rate(group, 4))
        lst_cv_ma5_rate.append(make_cv_maN_rate(group))

        lst_ud_3d.append(make_ud_Nd(group, 3))
        lst_ud_4d.append(make_ud_Nd(group, 4))
        lst_ud_5d.append(make_ud_Nd(group))

        lst_cv3d_diff_rate.append(make_cvNd_diff_rate(group,3))
        lst_cv4d_diff_rate.append(make_cvNd_diff_rate(group,4))
        lst_cv5d_diff_rate.append(make_cvNd_diff_rate(group))




    #Dataframe 합치기, concat 이용
    g_cv_diff_value = pd.concat(lst_cv_diff_value)

    g_cv_diff_rate = pd.concat(lst_cv_diff_rate)

    g_cv_ma3_value =pd.concat(lst_cv_ma3_value)
    g_cv_ma4_value = pd.concat(lst_cv_ma4_value)
    g_cv_ma5_value = pd.concat(lst_cv_ma5_value)

    g_cv_ma3_rate=pd.concat(lst_cv_ma3_rate)
    g_cv_ma4_rate = pd.concat(lst_cv_ma4_rate)
    g_cv_ma5_rate = pd.concat(lst_cv_ma5_rate)

    g_ud_3d=pd.concat(lst_ud_3d)
    g_ud_4d = pd.concat(lst_ud_4d)
    g_ud_5d = pd.concat(lst_ud_5d)

    g_cv3d_diff_rate=pd.concat(lst_cv3d_diff_rate)
    g_cv4d_diff_rate = pd.concat(lst_cv4d_diff_rate)
    g_cv5d_diff_rate = pd.concat(lst_cv5d_diff_rate)



    #새로운 stock_history_add를 만들기 위해 컬럼 값 넣어주기.
    df["cv_diff_value"] = g_cv_diff_value

    df["cv_diff_rate"] = g_cv_diff_rate

    df["cv_ma3_value"] = g_cv_ma3_value
    df["cv_ma4_value"] = g_cv_ma4_value
    df["cv_ma5_value"] = g_cv_ma5_value

    df["cv_ma3_rate"] = g_cv_ma3_rate
    df["cv_ma4_rate"] = g_cv_ma4_rate
    df["cv_ma5_rate"] = g_cv_ma5_rate

    df["ud_3d"] = g_ud_3d
    df["ud_4d"] = g_ud_4d
    df["ud_5d"] = g_ud_5d

    df["cv3d_diff_rate"] = g_cv3d_diff_rate
    df["cv4d_diff_rate"] = g_cv4d_diff_rate
    df["cv5d_diff_rate"] = g_cv5d_diff_rate



    #새로운 add.csv파일을 만들어 저장.
    df.to_csv("stock_history_add.csv", index=False, encoding="ms949")









