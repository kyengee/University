import pandas

df = pandas.read_csv("stock_history.csv", encoding='CP949')

for name, group in df.groupby("stockname"):
	print(name)
	group = group.sort_values(["basic_date"], ascending=[True])
	print(group.basic_date.key)
	break;

