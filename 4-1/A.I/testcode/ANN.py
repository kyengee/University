import numpy as np
import matplotlib.pyplot as plt
from mnist import load_mnist
from PIL import Image

(x_train, t_train), (x_test, t_test) = load_mnist(flatten=True,normalize=False)
testsheet = x_test.T

def test(num):
    for pat in range(0, nTrainingPats, 1):
        inp = np.hstack([testsheet[:,pat], np.array([1])])
        hiddenNetInputs = np.dot(hiddenWeights, inp)
        hiddenStates = sigmoidFunc(hiddenNetInputs)
        hidStatesBias = np.hstack([hiddenStates, np.array([1])])
        outputNetInputs = np.dot(outputWeights, hidStatesBias)
        outputStates = sigmoidFunc(outputNetInputs)

def img_show(num):
    img = x_test[num]
    label = t_test[num]
    img = img.reshape(28, 28) # 형상을 원래 이미지의 크기로 변형
    img_show(img)

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
nEpochs = 3000#x_train.shape[0]

for pat in range(0, nPats, 1):
    target[t_train[pat],pat] = 1

print(t_train[0])
print(target[:,0])
print(t_train[1])
print(target[:,1])
print(t_train[2])
print(target[:,2])


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

a = np.arange(0,nEpochs,1)
plt.plot(a,ErrorsLastEpochs[a])
plt.show()


