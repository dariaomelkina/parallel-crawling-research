from scipy import stats
import numpy
ALPHA = 1e-3

def student_test(distributions):
    # Hypotheses that all the data has normal distribution cannot be rejected
    # Performing Student t-test:
    epoll_data, thread_data, process_data = [dist["data"] for dist in distributions]

    t_stat1, p1 = stats.ttest_ind(epoll_data, process_data)
    t_stat2, p2 = stats.ttest_ind(epoll_data, thread_data)
    t_stat3, p3 = stats.ttest_ind(process_data, thread_data)

    # Displaying test results
    print("\nSTUDENT T-TEST\n" + "*" * 95)
    print(f"Epoll and Process per socket: t = {round(t_stat1, 2)} , p = {'%.2g' % p1}\n" + "*" * 95)
    print(f"Epoll and Thread per socket: t = {round(t_stat2, 2)} , p = {'%.2g' % p2}\n" + "*" * 95)
    print(f"Process per socket and Thread per socket: t = {round(t_stat3, 2)} , p = {'%.2g' % p3}\n" + "*" * 95)

    # Checking if we have same distributions (testing null hypotheses)
    print("\nCOMPARING DISTRIBUTIONS\n" + "*" * 95)

    same_e_p = p1 >= ALPHA
    same_e_t = p2 >= ALPHA
    same_t_p = p3 >= ALPHA

    if same_e_p:
        print("We cannot reject hypotheses, that Epoll and Process per socket "
                "are not significantly different \nfrom each other.\n" + "*" * 95)
    else:
        print("We reject hypotheses, that Epoll and Process per socket "
                "are not significantly different \nfrom each other. (they are different, in other words)")
        print("Comparing means:")
        m1 = round(numpy.mean(epoll_data), 2)
        m2 = round(numpy.mean(process_data), 2)
        print(f"Epoll mean = {m1}")
        print(f"Process per socket mean = {m2}")
        if m1 < m2:
            print(f"Epoll has mean smaller by {round(100 - (m1 / m2) * 100, 2)}%\n" + "*" * 95)
        else:
            print(f"Process per socket has mean smaller by {round(100 - (m2 / m1) * 100, 2)}%\n" + "*" * 95)

    if same_e_t:
        print("We cannot reject hypotheses, that Epoll and Thread per socket "
                "are not significantly different \nfrom each other.\n" + "*" * 95)
    else:
        print("We reject hypotheses, that Epoll and Thread per socket "
                "are not significantly different \nfrom each other. (they are different, in other words)")
        print("Comparing means:")
        m1 = round(numpy.mean(epoll_data), 2)
        m2 = round(numpy.mean(thread_data), 2)
        print(f"Epoll mean = {m1}")
        print(f"Thread per socket mean = {m2}")
        if m1 < m2:
            print(f"Epoll has mean smaller by {round(100 - (m1 / m2) * 100, 2)}%\n" + "*" * 95)
        else:
            print(f"Thread per socket has mean smaller by {round(100 - (m2 / m1) * 100, 2)}%\n" + "*" * 95)

    if same_t_p:
        print("We cannot reject hypotheses, that Thread per socket and Process per socket "
                "are not significantly \ndifferent from each other.\n" + "*" * 95)
    else:
        print("We reject hypotheses, that Thread per socket and Process per socket "
                "are not significantly \ndifferent from each other. (they are different, in other words)")
        print("Comparing means:")
        m1 = round(numpy.mean(thread_data), 2)
        m2 = round(numpy.mean(process_data), 2)
        print(f"Thread per socket mean = {m1}")
        print(f"Process per socket mean = {m2}")
        if m1 < m2:
            print(f"Thread per socket has mean smaller by {round(100 - (m1 / m2) * 100, 2)}%\n" + "*" * 95)
        else:
            print(f"Process per socket has mean smaller by {round(100 - (m2 / m1) * 100, 2)}%\n" + "*" * 95)




    # # Performing Wilcoxon test:
    # w_stat1, w_p1 = stats.wilcoxon(epoll_data, process_data)
    # w_stat2, w_p2 = stats.wilcoxon(epoll_data, thread_data)
    # w_stat3, w_p3 = stats.wilcoxon(process_data, thread_data)

    # # Displaying test results
    # print("\nWILCOXON TEST\n" + "*" * 95)
    # print(f"Epoll and Process per socket: t = {round(w_stat1, 2)} , p = {'%.2g' % w_p1}\n" + "*" * 95)
    # print(f"Epoll and Thread per socket: t = {round(w_stat2, 2)} , p = {'%.2g' % w_p2}\n" + "*" * 95)
    # print(f"Process per socket and Thread per socket: t = {round(w_stat3, 2)} , p = {'%.2g' % w_p3}\n" + "*" * 95)

    # # TODO: check if that test is performed correctly

    # w_same_e_p = w_p1 >= alpha
    # w_same_e_t = w_p2 >= alpha
    # w_same_t_p = w_p3 >= alpha

    # if w_same_e_p:
    #     print("We cannot reject hypotheses, that Epoll and Process per socket "
    #           "are not significantly different \nfrom each other.\n" + "*" * 95)
    # else:
    #     print("We reject hypotheses, that Epoll and Process per socket "
    #           "are not significantly different \nfrom each other. (they are different, in other words)")
    #     print("Comparing minimums:")
    #     m1 = round(numpy.min(epoll_data), 2)
    #     m2 = round(numpy.min(process_data), 2)
    #     print(f"Epoll minimum = {m1}")
    #     print(f"Process per socket minimum = {m2}")
    #     if m1 < m2:
    #         print(f"Epoll has minimum smaller by {round(100 - (m1 / m2) * 100, 2)}%\n" + "*" * 95)
    #     else:
    #         print(f"Process per socket has minimum smaller by {round(100 - (m2 / m1) * 100, 2)}%\n" + "*" * 95)

    # if w_same_e_t:
    #     print("We cannot reject hypotheses, that Epoll and Thread per socket "
    #           "are not significantly different \nfrom each other.\n" + "*" * 95)
    # else:
    #     print("We reject hypotheses, that Epoll and Thread per socket "
    #           "are not significantly different \nfrom each other. (they are different, in other words)")
    #     print("Comparing minimums:")
    #     m1 = round(numpy.min(epoll_data), 2)
    #     m2 = round(numpy.min(thread_data), 2)
    #     print(f"Epoll minimum = {m1}")
    #     print(f"Thread per socket minimum = {m2}")
    #     if m1 < m2:
    #         print(f"Epoll has minimum smaller by {round(100 - (m1 / m2) * 100, 2)}%\n" + "*" * 95)
    #     else:
    #         print(f"Thread per socket has minimum smaller by {round(100 - (m2 / m1) * 100, 2)}%\n" + "*" * 95)

    # if w_same_t_p:
    #     print("We cannot reject hypotheses, that Thread per socket and Process per socket "
    #           "are not significantly \ndifferent from each other.\n" + "*" * 95)
    # else:
    #     print("We reject hypotheses, that Thread per socket and Process per socket "
    #           "are not significantly \ndifferent from each other. (they are different, in other words)")
    #     print("Comparing minimums:")
    #     m1 = round(numpy.min(thread_data), 2)
    #     m2 = round(numpy.min(process_data), 2)
    #     print(f"Thread per socket minimum = {m1}")
    #     print(f"Process per socket minimum = {m2}")
    #     if m1 < m2:
    #         print(f"Thread per socket has minimum smaller by {round(100 - (m1 / m2) * 100, 2)}%\n" + "*" * 95)
    #     else:
    #         print(f"Process per socket has minimum smaller by {round(100 - (m2 / m1) * 100, 2)}%\n" + "*" * 95)



    # # Performing Wilcoxon test:
    # w_stat1, w_p1 = stats.wilcoxon(epoll_data, process_data)
    # w_stat2, w_p2 = stats.wilcoxon(epoll_data, thread_data)
    # w_stat3, w_p3 = stats.wilcoxon(process_data, thread_data)

    # # Displaying test results
    # print("\nWILCOXON TEST\n" + "*" * 95)
    # print(f"Epoll and Process per socket: t = {round(w_stat1, 2)} , p = {'%.2g' % w_p1}\n" + "*" * 95)
    # print(f"Epoll and Thread per socket: t = {round(w_stat2, 2)} , p = {'%.2g' % w_p2}\n" + "*" * 95)
    # print(f"Process per socket and Thread per socket: t = {round(w_stat3, 2)} , p = {'%.2g' % w_p3}\n" + "*" * 95)

    # # TODO: check if that test is performed correctly

    # w_same_e_p = w_p1 >= alpha
    # w_same_e_t = w_p2 >= alpha
    # w_same_t_p = w_p3 >= alpha

    # if w_same_e_p:
    #     print("We cannot reject hypotheses, that Epoll and Process per socket "
    #           "are not significantly different \nfrom each other.\n" + "*" * 95)
    # else:
    #     print("We reject hypotheses, that Epoll and Process per socket "
    #           "are not significantly different \nfrom each other. (they are different, in other words)")
    #     print("Comparing minimums:")
    #     m1 = round(numpy.min(epoll_data), 2)
    #     m2 = round(numpy.min(process_data), 2)
    #     print(f"Epoll minimum = {m1}")
    #     print(f"Process per socket minimum = {m2}")
    #     if m1 < m2:
    #         print(f"Epoll has minimum smaller by {round(100 - (m1 / m2) * 100, 2)}%\n" + "*" * 95)
    #     else:
    #         print(f"Process per socket has minimum smaller by {round(100 - (m2 / m1) * 100, 2)}%\n" + "*" * 95)

    # if w_same_e_t:
    #     print("We cannot reject hypotheses, that Epoll and Thread per socket "
    #           "are not significantly different \nfrom each other.\n" + "*" * 95)
    # else:
    #     print("We reject hypotheses, that Epoll and Thread per socket "
    #           "are not significantly different \nfrom each other. (they are different, in other words)")
    #     print("Comparing minimums:")
    #     m1 = round(numpy.min(epoll_data), 2)
    #     m2 = round(numpy.min(thread_data), 2)
    #     print(f"Epoll minimum = {m1}")
    #     print(f"Thread per socket minimum = {m2}")
    #     if m1 < m2:
    #         print(f"Epoll has minimum smaller by {round(100 - (m1 / m2) * 100, 2)}%\n" + "*" * 95)
    #     else:
    #         print(f"Thread per socket has minimum smaller by {round(100 - (m2 / m1) * 100, 2)}%\n" + "*" * 95)

    # if w_same_t_p:
    #     print("We cannot reject hypotheses, that Thread per socket and Process per socket "
    #           "are not significantly \ndifferent from each other.\n" + "*" * 95)
    # else:
    #     print("We reject hypotheses, that Thread per socket and Process per socket "
    #           "are not significantly \ndifferent from each other. (they are different, in other words)")
    #     print("Comparing minimums:")
    #     m1 = round(numpy.min(thread_data), 2)
    #     m2 = round(numpy.min(process_data), 2)
    #     print(f"Thread per socket minimum = {m1}")
    #     print(f"Process per socket minimum = {m2}")
    #     if m1 < m2:
    #         print(f"Thread per socket has minimum smaller by {round(100 - (m1 / m2) * 100, 2)}%\n" + "*" * 95)
    #     else:
    #         print(f"Process per socket has minimum smaller by {round(100 - (m2 / m1) * 100, 2)}%\n" + "*" * 95)



def wilcoxon_test(distributions):
    epoll_data, thread_data, process_data = [dist["data"] for dist in distributions]
    
    # Performing Wilcoxon test:
    w_stat1, w_p1 = stats.wilcoxon(epoll_data, process_data)
    w_stat2, w_p2 = stats.wilcoxon(epoll_data, thread_data)
    w_stat3, w_p3 = stats.wilcoxon(process_data, thread_data)

    # Displaying test results
    print("\nWILCOXON TEST\n" + "*" * 95)
    print(f"Epoll and Process per socket: t = {round(w_stat1, 2)} , p = {'%.2g' % w_p1}\n" + "*" * 95)
    print(f"Epoll and Thread per socket: t = {round(w_stat2, 2)} , p = {'%.2g' % w_p2}\n" + "*" * 95)
    print(f"Process per socket and Thread per socket: t = {round(w_stat3, 2)} , p = {'%.2g' % w_p3}\n" + "*" * 95)

    # TODO: check if that test is performed correctly

    w_same_e_p = w_p1 >= ALPHA
    w_same_e_t = w_p2 >= ALPHA
    w_same_t_p = w_p3 >= ALPHA

    if w_same_e_p:
        print("We cannot reject hypotheses, that Epoll and Process per socket "
              "are not significantly different \nfrom each other.\n" + "*" * 95)
    else:
        print("We reject hypotheses, that Epoll and Process per socket "
              "are not significantly different \nfrom each other. (they are different, in other words)")
        print("Comparing minimums:")
        m1 = round(numpy.min(epoll_data), 2)
        m2 = round(numpy.min(process_data), 2)
        print(f"Epoll minimum = {m1}")
        print(f"Process per socket minimum = {m2}")
        if m1 < m2:
            print(f"Epoll has minimum smaller by {round(100 - (m1 / m2) * 100, 2)}%\n" + "*" * 95)
        else:
            print(f"Process per socket has minimum smaller by {round(100 - (m2 / m1) * 100, 2)}%\n" + "*" * 95)

    if w_same_e_t:
        print("We cannot reject hypotheses, that Epoll and Thread per socket "
              "are not significantly different \nfrom each other.\n" + "*" * 95)
    else:
        print("We reject hypotheses, that Epoll and Thread per socket "
              "are not significantly different \nfrom each other. (they are different, in other words)")
        print("Comparing minimums:")
        m1 = round(numpy.min(epoll_data), 2)
        m2 = round(numpy.min(thread_data), 2)
        print(f"Epoll minimum = {m1}")
        print(f"Thread per socket minimum = {m2}")
        if m1 < m2:
            print(f"Epoll has minimum smaller by {round(100 - (m1 / m2) * 100, 2)}%\n" + "*" * 95)
        else:
            print(f"Thread per socket has minimum smaller by {round(100 - (m2 / m1) * 100, 2)}%\n" + "*" * 95)

    if w_same_t_p:
        print("We cannot reject hypotheses, that Thread per socket and Process per socket "
              "are not significantly \ndifferent from each other.\n" + "*" * 95)
    else:
        print("We reject hypotheses, that Thread per socket and Process per socket "
              "are not significantly \ndifferent from each other. (they are different, in other words)")
        print("Comparing minimums:")
        m1 = round(numpy.min(thread_data), 2)
        m2 = round(numpy.min(process_data), 2)
        print(f"Thread per socket minimum = {m1}")
        print(f"Process per socket minimum = {m2}")
        if m1 < m2:
            print(f"Thread per socket has minimum smaller by {round(100 - (m1 / m2) * 100, 2)}%\n" + "*" * 95)
        else:
            print(f"Process per socket has minimum smaller by {round(100 - (m2 / m1) * 100, 2)}%\n" + "*" * 95)
