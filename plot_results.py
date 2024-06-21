import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv("results.txt")

df["InsertionTime"] = df["InsertionTime"] * 1000
df["SearchTime"] = df["SearchTime"] * 1000

fig, ax = plt.subplots(figsize=(10, 6))

ax.plot(df["Size"], df["InsertionTime"], label="Insertion", linestyle='-')
ax.plot(df["Size"], df["SearchTime"], label="Search", linestyle='-')

ax.grid(True, linestyle='--', linewidth=0.5)

ax.set_xlabel("Количество элементов", fontsize=12)
ax.set_ylabel("Время (мс)", fontsize=12)
ax.set_title("Производительность AVL-дерева", fontsize=14)

ax.legend(fontsize=10)

plt.show()