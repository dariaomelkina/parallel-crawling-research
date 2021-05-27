import sys
import pandas as pd
from scipy import stats
import numpy
import plotly.express as px
import plotly.graph_objects as go

NUMBER_OF_PARAMETER_ROWS = 9
NUMBER_OF_WARNING_ROWS = 1
NUMBER_Of_SKIP_ROWS = 5

if __name__ == "__main__":
    ###################################################################################################################
    # Read csv files
    df = pd.read_csv(sys.argv[1],
                           skiprows=range(0, NUMBER_OF_PARAMETER_ROWS))
    data = df['real_time'][NUMBER_Of_SKIP_ROWS:] / 1000000000
    ###################################################################################################################
    # Plot customizations
    custom_labels = {"x": "Time, s",
                     "y": "Number of iterations"}
    ###################################################################################################################
    # Creating bar plot of the distribution
    fig = px.histogram(x=data,
                       nbins=50,
                       title="Results distribution",
                       labels=custom_labels)
    fig.write_image("result-plots/test-plot.png")
