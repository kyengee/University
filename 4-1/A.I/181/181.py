# coding: utf-8
import sys, os
sys.path.append(os.pardir)  # 부모 디렉터리의 파일을 가져올 수 있도록 설정
import numpy as np
from common.layers import *
from common.gradient import numerical_gradient
from collections import OrderedDict


class TwoLayerNet:

    def __init__(self, input_size, hidden_size, output_size, weight_init_std = 0.01):
        # 가중치 초기화
        self.params = {}
        #input-> hidden으로 가는 첫번째 layer의 가중치에 랜덤값을 넣는다.
        self.params['W1'] = weight_init_std * np.random.randn(input_size, hidden_size)
        #input-> hidden으로 가는 첫번째 layer의 bias값을 넣는다.
        self.params['b1'] = np.zeros(hidden_size)
        #input-> hidden으로 가는 두번째 layer의 가중치에 랜덤값을 넣는다.
        self.params['W2'] = weight_init_std * np.random.randn(hidden_size, output_size) 
        #input-> hidden으로 가는 두번째 layer의 bias값을 넣는다.
        self.params['b2'] = np.zeros(output_size)

        # 계층 생성
        self.layers = OrderedDict()
        #Affine 계층생성
        self.layers['Affine1'] = Affine(self.params['W1'], self.params['b1'])
        #Relu 계층생성 
        self.layers['Relu1'] = Relu()
        #Affine 계층생성
        self.layers['Affine2'] = Affine(self.params['W2'], self.params['b2'])
        #Softmax계층생성
        self.lastLayer = SoftmaxWithLoss()
        
    #순전파 계산
    def predict(self, x):
        for layer in self.layers.values():
            x = layer.forward(x)
        
        return x
        
    # x : 입력 데이터, t : 정답 레이블
    def loss(self, x, t):
        #예측(추론)을 수행한다.
        y = self.predict(x)
        #Softmax계산까지 마친 값을 반환한다.
        return self.lastLayer.forward(y, t)
    
    def accuracy(self, x, t):
        #예측(추론)을 수행한다.
        y = self.predict(x)
        #정확도를 구한다. 
        y = np.argmax(y, axis=1)
        if t.ndim != 1 : t = np.argmax(t, axis=1)
        
        accuracy = np.sum(y == t) / float(x.shape[0])
        return accuracy
        
    # x : 입력 데이터, t : 정답 레이블
    def numerical_gradient(self, x, t):
        #매개변수의 기울기를 오차역전파법으로 구한다.
        loss_W = lambda W: self.loss(x, t)
        
        grads = {}
        #전 계층에 수행 
        grads['W1'] = numerical_gradient(loss_W, self.params['W1'])
        grads['b1'] = numerical_gradient(loss_W, self.params['b1'])
        grads['W2'] = numerical_gradient(loss_W, self.params['W2'])
        grads['b2'] = numerical_gradient(loss_W, self.params['b2'])
        
        return grads
        
    def gradient(self, x, t):
        # 순전파 계산
        self.loss(x, t)

        # 역전파 계산
        dout = 1
        dout = self.lastLayer.backward(dout)
        
        layers = list(self.layers.values())
        layers.reverse()
        for layer in layers:
            dout = layer.backward(dout)

        # 결과 저장
        grads = {}
        grads['W1'], grads['b1'] = self.layers['Affine1'].dW, self.layers['Affine1'].db
        grads['W2'], grads['b2'] = self.layers['Affine2'].dW, self.layers['Affine2'].db

        return grads

