import sys
import plotly.express as px

if __name__ == "__main__":
    # file = sys.argv[1]
    # TODO: read csv file

    # TODO: change to real input data
    data = [134, 456, 213, 234, 278, 190, 191, 135, 476, 223, 214, 178, 199, 171, 234, 356, 313, 334, 378, 290, 291]
    
    # I dont think we need a scatter plot
    # fig = px.scatter(x=data, y=range(0, len(data)))

    fig = px.bar(x=data, y=range(0, len(data)))
    fig.show()
