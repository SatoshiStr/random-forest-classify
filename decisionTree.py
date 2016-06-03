
DATA_SUM = 10 * 10000
#DATA_SUM = 2177020

#ALL_ARG_SUM = 11392
# 56->0.7  123->0.9  406->0.99
USE_ARG = 20
TREE_SUM = 6000


from ctypes import *
# args = (45, 203, 204, 521, 522, 542, 543, 544, 545, 546, 547, 577, 578, 579, 580, 
# 589, 1593, 1594, 1595, 1596, 1601, 1602, 1614, 1615, 1616, 2019, 2020, 2021, 
# 2023, 2024, 2026, 2027, 2029, 2035, 2037, 2038, 2039, 2040, 2042, 2044, 2054, 
# 2055, 2082, 2084, 2086, 2087, 2089, 2092, 2163, 2164, 2169, 2170, 2173, 2174, 
# 2179, 2180, 2188, 2189, 2192, 2193, 2198, 2199, 2204, 2205, 2210, 2211, 2224, 
# 2225, 2228, 2229, 2230, 2231, 2234, 2235, 2236, 2237, 2240, 2241, 9011, 9018, 
# 9067, 9085, 9133, 9150, 9151, 9153, 9154, 9163, 9165, 9253, 10171, 10172, 
# 10173, 10177, 11179, 11180, 11181, 11182, 11223, 11224, 11235, 11236, 11259, 
# 11260, 11262, 11282, 11292, 11294, 11295, 11296, 11297, 11298, 11306, 11326, 
# 11328, 11329, 11368, 11371, 11377, 11384, 11386, 11387, 11390)
args = (16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 47, 48, 203, 204, 205, 206, 521, 522, 523, 524, 525, 526, 527, 542, 543, 544, 545, 546, 547, 548, 549, 550, 551, 552, 577, 578, 579, 580, 581, 582, 583, 584, 585, 586, 588, 589, 593, 594, 597, 602, 604, 610, 613, 626, 627, 631, 676, 1592, 1593, 1594, 1595, 1596, 1601, 1602, 1603, 1604, 1605, 1614, 1615, 1616, 1617, 1618, 1619, 1620, 1621, 1622, 1623, 1624, 2019, 2020, 2021, 2023, 2024, 2025, 2026, 2027, 2029, 2035, 2037, 2038, 2039, 2040, 2041, 2042, 2043, 2044, 2045, 2054, 2055, 2056, 2057, 2078, 2080, 2082, 2084, 2085, 2086, 2087, 2089, 2090, 2092, 2157, 2158, 2163, 2164, 2165, 2166, 2167, 2168, 2169, 2170, 2171, 2172, 2173, 2174, 2175, 2176, 2177, 2178, 2179, 2180, 2185, 2186, 2188, 2189, 2192, 2193, 2194, 2195, 2196, 2197, 2198, 2199, 2204, 2205, 2206, 2207, 2210, 2211, 2214, 2215, 2216, 2217, 2218, 2219, 2220, 2221, 2222, 2223, 2224, 2225, 2228, 2229, 2230, 2231, 2232, 2233, 2234, 2235, 2236, 2237, 2238, 2239, 2240, 2241, 2249, 2262, 2267, 2329, 2330, 2340, 2355, 2367, 2384, 2402, 2439, 2543, 2553, 2562, 2571, 2593, 2662, 2675, 2685, 2895, 2937, 2975, 2989, 3007, 3065, 3517, 3615, 3677, 4025, 4054, 4214, 4421, 4843, 4874, 5114, 5792, 5908, 6089, 6515, 6669, 8918, 8935, 8946, 8962, 8969, 8977, 8979, 8987, 8989, 9011, 9015, 9017, 9018, 9020, 9023, 9027, 9034, 9036, 9055, 9066, 9067, 9085, 9086, 9098, 9100, 9121, 9127, 9133, 9141, 9150, 9151, 9153, 9154, 9155, 9158, 9159, 9160, 9161, 9162, 9163, 9165, 9186, 9203, 9253, 10155, 10170, 10171, 10172, 10173, 10177, 10178, 10179, 10180, 10181, 10182, 10183, 10184, 10185, 10186, 10187, 10188, 10189, 10190, 10191, 10192, 10193, 10194, 10195, 10196, 10198, 10199, 10200, 10201, 10202, 10204, 10205, 10206, 10207, 10208, 10209, 10210, 10212, 10214, 10217, 10223, 10261, 10269, 10271, 10275, 10278, 10296, 10325, 10341, 10358, 10429, 10483, 10506, 10520, 10529, 10541, 10546, 10581, 10614, 10624, 10629, 10689, 10722, 10752, 10778, 11177, 11179, 11180, 11181, 11182, 11183, 11184, 11185, 11187, 11188, 11189, 11191, 11194, 11196, 11199, 11223, 11224, 11225, 11226, 11227, 11235, 11236, 11238, 11239, 11259, 11260, 11262, 11282, 11292, 11293, 11294, 11295, 11296, 11297, 11298, 11306, 11326, 11328, 11329, 11353, 11354, 11356, 11357, 11358, 11359, 11360, 11361, 11366, 11368, 11371, 11374, 11377, 11379, 11380, 11382, 11383, 11384, 11386, 11387, 11389, 11390, 11392)
args = [c_short(num) for num in args]
args = tuple(args)


def get_attr(arg_set, index):
    if index in arg_set:
        return c_bool(True)
    else:
        return c_bool(False)

def makeTrainData():
    filename = 'train.txt'
    fp = open(filename, 'r')
    train_args = []
    labels = []
    line_cnt = 0
    while(line_cnt < DATA_SUM):
        line_cnt += 1
        line = fp.readline()
        arr = line.split()
        #
        labels.append(int(arr[0]))
        #
        train_arg = set()
        for index in range(1, len(arr)):
            right = arr[index].find(':')
            train_arg.add(int(arr[index][:right]))
        train_args.append(train_arg)
    fp.close()
    # rearrange format
    X = []
    Y = labels
    for arg_set in train_args:
        data = []
        for index in args:
            data.append(get_attr(arg_set, index))
        X.append(data)
        # print data
    # for a in X:
    #     print a
    return X, Y
    # for item in train_args:
    #     print '=='
    #     for arg in item:
    #         print arg,
    #     print

def makeTestSet():
    filename = 'test.txt'
    fp = open(filename, 'r')
    train_args = []
    indexes = []
    line_cnt = 0
    for line in fp:
        arr = line.split()
        #
        indexes.append(int(arr[0]))
        # print 'index ', int(arr[0])
        #
        train_arg = set()
        for index in range(1, len(arr)):
            right = arr[index].find(':')
            train_arg.add(int(arr[index][:right]))
        train_args.append(train_arg)
    fp.close()
    # return train_args, indexes
    # rearrange format
    X = []
    for arg_set in train_args:
        data = []
        for index in args:
            data.append(get_attr(arg_set, index))
        # print data
        X.append(data)
    return X, indexes



from datetime import datetime
from sklearn.ensemble import RandomForestClassifier

if __name__ == '__main__':
    print 'run', datetime.now()
    print '\ttrain-size %d, selected-arg-size %d, use-arg %d, tree %d' % \
        (DATA_SUM, len(args), USE_ARG, TREE_SUM)

    start = datetime.now()
    X, Y = makeTrainData()
    print 'make data completed'
    end = datetime.now()
    print '    data process cost: ', end-start

    start = datetime.now()
    clf = RandomForestClassifier(n_estimators=TREE_SUM, max_features=USE_ARG,
        n_jobs=-1)
    clf = clf.fit(X, Y)
    end = datetime.now()
    print '    build %s tree cost: ' % TREE_SUM, end-start
    print '\taverage per tree', (end-start) / TREE_SUM
    del X
    del Y

    test_args, indexes = makeTestSet()
    print 'make test completed'

    start = datetime.now()
    arr = clf.predict(test_args)
    end = datetime.now()
    print 'predict completed'
    print '    cost', end-start
    del test_args

    fp = open('out.csv', 'w')
    fp.write('id,label\n')
    for id, label in zip(indexes, arr):
        fp.write('%d,%d\n' % (id, label))
    fp.close()



# clf.predict([[1, 1], [0, 0], [0, 1]])
# sudo apt-get install -y build-essential python-dev python-numpy \
#     python-setuptools python-scipy libatlas-dev python-matplotlib  \
# && sudo pip install -U scikit-learn
