def F(x: float) -> float:
    return x**5/5-(29*x**4)/40+(13*x**3)/6-(7*x**2)/2-(27*x)/5


def real_integral(a: float, b: float) -> float:
    return F(b) - F(a)
