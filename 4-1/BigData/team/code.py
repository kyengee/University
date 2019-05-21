import pandas

def make_cv_diff_rate(Dataframe):
	close_value_Series = Dataframe["close_value"]
	cv_diff_rate_Series = Dataframe["cv_diff_rate"]
	last_index = close_value_Series.index[-1]

	for index in Dataframe.index:
		if index == last_index: break
		cv_diff_rate_Series.at[index] = 100 - close_value_Series.at[index] / close_value_Series.at[index + 1] * 100
	print(cv_diff_rate_Series)

def make_ud_Nd(N, Dataframe):
	close_value_Series = Dataframe["close_value"]
	ud_Nd_Series = Dataframe["ud_" + str(N) + "d"]
	last_index = close_value_Series.index[-N]
	
	for index in Dataframe.index:
		if index == last_index: break
		val = 0
		for i in range(0,N,1):
			if close_value_Series.at[index + i] - close_value_Series.at[index + i + 1] > 0: 
				val += 1
			else: 
				val -= 1

		if val % N == 0:
			val = val / N
		else:
			val = 0
		ud_Nd_Series.at[index + 1] = val
	print(ud_Nd_Series)

def make_cvNd_diff_rate(N, Dataframe):
	close_value_Series = Dataframe["close_value"]
	cvNd_diff_rate_Series = Dataframe["cv" + str(N) + "d_diff_rate"]
	last_index = close_value_Series.index[-N]
	
	for index in Dataframe.index:
		if index == last_index: break
		cvNd_diff_rate_Series.at[index + 1] = (close_value_Series.at[index] - close_value_Series.at[index + N]) / close_value_Series.at[index + N]
	print(cvNd_diff_rate_Series)



df = pandas.read_csv("stock_history.csv", encoding='CP949')

for name, group in df.groupby("stockname"):
	make_cvNd_diff_rate(3, group)
	break;