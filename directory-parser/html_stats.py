import os
import numpy as np
import seaborn as sns
import matplotlib.pyplot as plt
import pandas as pd

file_sizes = []

for subdir, dirs, files in os.walk("test-websites"):
    for file in files:
        # print os.path.join(subdir, file)
        filepath = subdir + os.sep + file

        if filepath.endswith(".html"):
            file_stats = os.stat(filepath)
            # size of the file in Kilobytes
            file_size = round(file_stats.st_size / 1024)
            # print(filepath, file_size)
            file_sizes.append(file_size)

file_sizes = np.array(file_sizes)
print(file_sizes)

# sns.distplot(file_sizes, hist=True, kde=True,
#              bins=int(180), color='darkblue',
#              hist_kws={'edgecolor': 'black'},
#              kde_kws={'linewidth': 2})


# Density Plot with Rug Plot
sns.distplot(file_sizes, hist=False, kde=True, rug=True,
             color='darkblue',
             kde_kws={'linewidth': 2},
             rug_kws={'color': 'black'})

# Plot formatting
plt.title('Density Plot of the size of html file in Kb')
plt.xlabel('HTML size, Kb')
plt.ylabel('Density')
plt.xlim((0, max(file_sizes)))
plt.xticks(np.linspace(0, 3000, num=11))
plt.show()

df_describe = pd.DataFrame(file_sizes)
print(df_describe.describe())
