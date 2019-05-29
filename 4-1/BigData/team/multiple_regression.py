from collections import Counter
from functools import partial
from linear_algebra import dot, vector_add
from stats import median, standard_deviation
from probability import normal_cdf
from gradient_descent import minimize_stochastic
from simple_linear_regression import total_sum_of_squares
import math, random
from sklearn.linear_model import LinearRegression
from sklearn.linear_model import Ridge
import numpy as np
import pandas
from sklearn.preprocessing import scale


def predict(x_i, beta):
    return dot(x_i, beta)


def error(x_i, y_i, beta):
    print(predict(x_i, beta))
    return y_i - predict(x_i, beta)



def squared_error(x_i, y_i, beta):
    return error(x_i, y_i, beta) ** 2


def squared_error_gradient(x_i, y_i, beta):
    """the gradient corresponding to the ith squared error term"""
    return [-2 * x_ij * error(x_i, y_i, beta)
            for x_ij in x_i]


def estimate_beta(x, y):
    beta_initial = [random.random() for x_i in x[0]]
    return minimize_stochastic(squared_error,
                               squared_error_gradient,
                               x, y,
                               beta_initial,
                               0.001)


def multiple_r_squared(x, y, beta):
    sum_of_squared_errors = sum(error(x_i, y_i, beta) ** 2
                                for x_i, y_i in zip(x, y))
    return 1.0 - sum_of_squared_errors / total_sum_of_squares(y)


def bootstrap_sample(data):
    """randomly samples len(data) elements with replacement"""
    return [random.choice(data) for _ in data]


def bootstrap_statistic(data, stats_fn, num_samples):
    """evaluates stats_fn on num_samples bootstrap samples from data"""
    return [stats_fn(bootstrap_sample(data))
            for _ in range(num_samples)]


def estimate_sample_beta(sample):
    x_sample, y_sample = list(zip(*sample))  # magic unzipping trick
    return estimate_beta(x_sample, y_sample)


def p_value(beta_hat_j, sigma_hat_j):
    if beta_hat_j > 0:
        return 2 * (1 - normal_cdf(beta_hat_j / sigma_hat_j))
    else:
        return 2 * normal_cdf(beta_hat_j / sigma_hat_j)


#
# REGULARIZED REGRESSION
#

# alpha is a *hyperparameter* controlling how harsh the penalty is
# sometimes it's called "lambda" but that already means something in Python
def ridge_penalty(beta, alpha):
    return alpha * dot(beta[1:], beta[1:])


def squared_error_ridge(x_i, y_i, beta, alpha):
    """estimate error plus ridge penalty on beta"""
    return error(x_i, y_i, beta) ** 2 + ridge_penalty(beta, alpha)


def ridge_penalty_gradient(beta, alpha):
    """gradient of just the ridge penalty"""
    return [0] + [2 * alpha * beta_j for beta_j in beta[1:]]


def squared_error_ridge_gradient(x_i, y_i, beta, alpha):
    """the gradient corresponding to the ith squared error term
    including the ridge penalty"""
    return vector_add(squared_error_gradient(x_i, y_i, beta),
                      ridge_penalty_gradient(beta, alpha))


def estimate_beta_ridge(x, y, alpha):
    """use gradient descent to fit a ridge regression
    with penalty alpha"""
    beta_initial = [random.random() for x_i in x[0]]
    return minimize_stochastic(partial(squared_error_ridge, alpha=alpha),
                               partial(squared_error_ridge_gradient,
                                       alpha=alpha),
                               x, y,
                               beta_initial,
                               0.001)


def lasso_penalty(beta, alpha):
    return alpha * sum(abs(beta_i) for beta_i in beta[1:])


if __name__ == "__main__":
    df = pandas.read_csv("microtech.csv", encoding='CP949')

    # Data Settings
    # - 첫번째 값을 모두 1로 설정하여, 알파값(coef)을 포함하여 유추하도록 함.
    # - 2~4번째 값: 친구수, 근무시간, 박사학위여부

    result = df["cv3d_diff_rate"].tolist()

    close_value = df["close_value"].tolist()
    cv_diff_value = df["cv_diff_value"].tolist()
    cv_diff_rate = df["cv_diff_rate"].tolist()
    cv_ma3_value = df["cv_ma3_value"].tolist()
    cv_ma4_value = df["cv_ma4_value"].tolist()
    cv_ma5_value = df["cv_ma5_value"].tolist()
    cv_ma3_rate = df["cv_ma3_rate"].tolist()
    cv_ma4_rate = df["cv_ma4_rate"].tolist()
    cv_ma5_rate = df["cv_ma5_rate"].tolist()
    cv_diff_rate_rate = df["cv_diff_rate_rate"].tolist()
    ud_3d = df["ud_3d"].tolist()
    ud_4d = df["ud_4d"].tolist()
    ud_5d = df["ud_5d"].tolist()
    Skhynix_cv_diff_value = df["Skhynix_cv_diff_value"].tolist()
    samsung_cv_diff_value = df["samsung_cv_diff_value"].tolist()
    kosdaq_diff_rate = df["kosdaq_diff_rate"].tolist()

    x = np.array([np.ones(230),cv_diff_rate_rate ,ud_3d, cv_diff_rate,scale(Skhynix_cv_diff_value)])
    x = x.T
    x = x.astype(np.single)



    """
    # 15.3 모델학습하기
    random.seed(0)
    #beta = estimate_beta(x, daily_minutes_good) # [30.63, 0.972, -1.868, 0.911]
    #print("beta", beta)
    # scikit-learn을 쓴다면: fit_intercept=False : 알파를 베타의 첫항목으로 계산
    myreg = LinearRegression(False).fit(x[:140],result[:140])
    print("beta of LR:", myreg.coef_)
    beta = myreg.coef_
    # 15.5 적합성(Goodness of fit)
    print("r-squared", multiple_r_squared(x[140:], result[140:], beta))
    print()
    
    # 15.6 bootstrap
    print("digression: the bootstrap")
    # 101 points all very close to 100
    close_to_100 = [99.5 + random.random() for _ in range(101)]

    # 101 points, 50 of them near 0, 50 of them near 200, 1 of them near 100
    far_from_100 = ([99.5 + random.random()] +
                    [random.random() for _ in range(50)] +
                    [200 + random.random() for _ in range(50)])


    print("bootstrap_statistic(close_to_100, median, 10):")
    print(bootstrap_statistic(close_to_100, median, 10))
    print("bootstrap_statistic(far_from_100, median, 10):")
    print(bootstrap_statistic(far_from_100, median, 10))
    print()

    15.7 계수의 표준오차 (skip) 
    random.seed(0) # so that you get the same results as me
    bootstrap_betas = bootstrap_statistic(list(zip(x, daily_minutes_good)),
                                          estimate_sample_beta,
                                          100)

    bootstrap_standard_errors = [
        standard_deviation([beta[i] for beta in bootstrap_betas])
        for i in range(4)]

    print("bootstrap standard errors", bootstrap_standard_errors)
    print()

    print("p_value(30.63, 1.174)", p_value(30.63, 1.174))
    print("p_value(0.972, 0.079)", p_value(0.972, 0.079))
    print("p_value(-1.868, 0.131)", p_value(-1.868, 0.131))
    print("p_value(0.911, 0.990)", p_value(0.911, 0.990))
    print()
    """
    # 15.8 Regularization
    print("regularization")

    total = np.zeros([10])
    print(total)
    # (1) 교재방법
    print("(1) by Textbook")
    random.seed(0)
    for alpha in [0.0, 0.01, 0.1, 1, 10]:
        """
        beta = estimate_beta_ridge(x, result, alpha=alpha)
        print("alpha", alpha)
        print("beta", beta)
        # print("dot(beta[1:],beta[1:])", dot(beta[1:], beta[1:]))
        print("r-squared", multiple_r_squared(x, result, beta))
        print()
        """

    # (2) scikit-liearn 사용방법
    print("(2) by scikit-learn")
    for alpha in [0.0, 0.01, 0.1, 1, 10]:
        ridge_reg = Ridge(alpha, fit_intercept=False, solver="cholesky")
        ridge_reg.fit(x[:140], result[:140])
        beta = ridge_reg.coef_
        print("alpha", alpha)
        print("beta", beta)
        print("r-squared", multiple_r_squared(x[140:], result[140:], beta))
