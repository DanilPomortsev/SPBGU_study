import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

table = pd.read_csv('titanic.csv', delimiter=',')

men_sur = len(table.query('Sex == "male" & Survived == 1'))
men_died = len(table.query('Sex == "male" & Survived == 0'))

wemen_sur = len(table.query('Sex == "female" & Survived == 1'))
wemen_died = len(table.query('Sex == "female" & Survived == 0'))

df = pd.DataFrame([[men_sur, wemen_sur],
                   [men_died, wemen_died]],
                    ['survive', 'died'], ['men','weman'])

men = np.array([men_sur, men_died])
wemen = np.array([wemen_sur, wemen_died])
mylabels = ["men survive", "men died"]

#df.plot(kind='pie', subplots=True, figsize=(8, 4), autopct='%1.1f%%')
#plt.show()

first_class_sur = len(table.query('Survived == 1 & Pclass == 1'))
second_class_sur = len(table.query('Survived == 1 & Pclass == 2'))
third_class_sur = len(table.query('Survived == 1 & Pclass == 3'))

first_class_die = len(table.query('Survived == 0 & Pclass == 1'))
second_class_die = len(table.query('Survived == 0 & Pclass == 2'))
third_class_die = len(table.query('Survived == 0 & Pclass == 3'))

df = pd.DataFrame([[first_class_sur, second_class_sur, third_class_sur],
                   [first_class_die, second_class_die, third_class_die]],
                  ['survive','died'], ['first class', 'second class', 'third class'])
heatmap_plot = sns.heatmap(df, center=0, cmap='gist_ncar')
plt.show()


#df.plot(kind='pie', subplots=True, figsize=(8, 4), autopct='%1.1f%%')
#plt.show()


survive_age = table.query("Survived == 1 and not Age.isna()")['Age']
died_age = table.query("Survived == 0 and not Age.isna()")['Age']

fig, axs = plt.subplots(1, 2, figsize=(10, 5))

axs[0].set_xlabel('Age')
axs[0].set_ylabel('Quantity')
axs[1].set_xlabel('Age')
axs[1].set_ylabel('Quantity')

#survive_age.plot.hist(ax=axs[0], title="Survive")
#died_age.plot.hist(ax=axs[1], title="died")
#plt.show()


poor_sur = len(table.query('Survived == 1 & Fare < 25'))
poor_died = len(table.query('Survived == 0 & Fare < 25'))

rich_sur = len(table.query('Survived == 1 & Fare >= 25'))
rich_died = len(table.query('Survived == 0 & Fare >= 25'))

df = pd.DataFrame([[poor_sur, rich_sur],
                   [poor_died, rich_died]],
                  ['survive', 'died'], ['poor','rich'])


#df.plot(kind='pie', subplots=True, figsize=(8, 4), autopct='%1.1f%%')
#plt.show()
