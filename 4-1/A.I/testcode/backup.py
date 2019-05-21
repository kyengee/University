import numpy as np
import matplotlib.pyplot as plt
from mnist import load_mnist
from PIL import Image

(x_train, t_train), (x_test, t_test) = load_mnist(flatten=True,normalize=False)
print(x_train.shape)
print(t_train.shape)
print(x_test.shape)
print(t_test.shape)


def sigmoidFunc(totallnput):
    return 1.0 / (np.ones(totallnput.shape) + np.exp(-1.0 * totallnput))

def outputDeltas(output, target):
    #모두 벡터의 연산
    sigmoidDeriv = output * (np.ones(output.shape) - output)
    return 2 * (target - output) * sigmoidDeriv

def hiddenDeltas(outputDeltas, hiddenOutputs, outputWeights):
    sigmoidDeriv = hiddenOutputs * (np.ones(hiddenOutputs.shape) - hiddenOutputs)
    return (np.dot(outputWeights.T, outputDeltas.T)) *sigmoidDeriv

patterns = x_train.T
nPats = x_train.shape[0]
nTrainingPats = 784
nTestPats = 784
nInputs = x_train.shape[1]
nHidden = 10
nOutputs = 10

hiddenWeights = 0.5 * (np.random.rand(nHidden, nInputs+1) - np.ones((nHidden, nInputs+1)) * 0.5)
outputWeights = 0.5 * (np.random.rand(nOutputs, nHidden+1) - np.ones((nOutputs, nHidden+1)) * 0.5)

input = patterns
target = np.zeros([nOutputs, nPats])
classNum = 0
eta = 0.1
nEpochs = 1000

for pat in range(0, nPats, 1):
    target[t_train[pat]-1:,pat] = 1

ErrorsLastEpochs = np.zeros((nEpochs))
TestErrorsLastEpochs = np.zeros((nEpochs))

#학습
for epoch in range(0, nEpochs, 1):
    sumSqrError = 0.0

    outputWGrad = np.zeros(outputWeights.shape)
    hiddenWGrad = np.zeros(hiddenWeights.shape)

    for pat in range(0, nTrainingPats, 1):
        inp = np.hstack([input[:,pat], np.array([1])])
        hiddenNetInputs = np.dot(hiddenWeights, inp)
        hiddenStates = sigmoidFunc(hiddenNetInputs)
        hidStatesBias = np.hstack([hiddenStates, np.array([1])])
        outputNetInputs = np.dot(outputWeights, hidStatesBias)
        outputStates = sigmoidFunc(outputNetInputs)

        targetStates = target[:,pat]
        error = outputStates - targetStates
        sumSqrError = sumSqrError + np.dot(error, error)
        outputDel = outputDeltas(outputStates, targetStates)
        outputWGrad = outputWGrad + np.dot(np.array([outputDel]).T, np.array([hidStatesBias]))
        hiddenDel = hiddenDeltas(outputDel, hidStatesBias, outputWeights)
        hiddenDelArray = np.array([hiddenDel])
        hiddenWGrad = hiddenWGrad + np.dot(hiddenDelArray[:,0:nHidden].T, np.array([inp]))


    ErrorsLastEpochs[epoch] = sumSqrError
    outputWchange = eta * outputWGrad
    outputWeights = outputWeights + outputWchange
    hiddenWChange = eta * hiddenWGrad
    hiddenWeights = hiddenWeights + hiddenWChange
'''
#테스트
for epoch in range(0, nEpochs, 1):
    sumSqrTestError = 0.0

    for pat in range(0, nTrainingPats, 1):
        inp = np.hstack([input[:,pat], np.array([1])])
        hiddenNetInputs = np.dot(hiddenWeights, inp)
        hiddenStates = sigmoidFunc(hiddenNetInputs)
        hidStatesBias = np.hstack([hiddenStates, np.array([1])])
        outputNetInputs = np.dot(outputWeights, hidStatesBias)
        outputStates = sigmoidFunc(outputNetInputs)

        targetStates = target[:,pat]
        error = outputStates - targetStates
        sumSqrTestError = sumSqrTestError + np.dot(error, error)

    TestErrorsLastEpochs[epoch] = sumSqrTestError

'''
a = np.arange(0,1000,1)
plt.plot(a,ErrorsLastEpochs[a])
plt.show()
'''
plt.plot(a,TestErrorsLastEpochs[a])
plt.show()
'''
