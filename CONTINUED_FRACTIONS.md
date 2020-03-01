$$
\begin{matrix}
\sum_{k = 1}^{n} (-1)^{k-1} \cdot 2^{-c_k} 
&=& (-1)^{1-1} 2^{-c_1}\left(
    1 + \sum_{k = 2}^{n} (-1)^{k-1} \cdot 2^{-(c_k - c_1)} 
    \right)\\
&=& \cfrac{1}{
    \cfrac{1}{
        2^{-c_1}
        \left(
            1 + \sum_{k = 2}^{n} (-1)^{k-1} \cdot 2^{-(c_k - c_1)} 
        \right)
    }
}
\\&=& \cfrac{1}{
    \cfrac{2^{c_1}}{
        1 + \sum_{k = 2}^{n} (-1)^{k-1} \cdot 2^{-(c_k - c_1)} 
    }
}
\\&=& \cfrac{1}{
    2^{c_1} + \cfrac{1}{
        -2^{-c_1} + \cfrac{-2^{-c_1}}{
            \sum_{k = 2}^{n} (-1)^{k-1} \cdot 2^{-(c_k - c_1)} 
        }
    }
}
\\&=& \cfrac{1}{
    2^{c_1} + \cfrac{1}{
        -2^{-c_1} + \cfrac{1}{
            -2^{c_1} \cdot \sum_{k = 2}^{n} (-1)^{k-1} \cdot 2^{-(c_k - c_1)} 
        }
    }
}
\\&=& \cfrac{1}{
    2^{c_1} + \cfrac{1}{
        -2^{-c_1} + \cfrac{1}{
            \sum_{k = 2}^{n} (-1)^{k} \cdot 2^{c_1-(c_k - c_1)} 
        }
    }
}
\\&=& \cfrac{1}{
    2^{c_1} + \cfrac{1}{
        -2^{-c_1} + \cfrac{1}{
            2^{-(c_2 - 2 c_1)} \cdot
            \sum_{k = 2}^{n} (-1)^{k} \cdot 2^{-(c_k - 2 c_1)} 
        }
    }
}
\\&=& \cfrac{1}{
    2^{c_1} + \cfrac{1}{
        -2^{-c_1} + \cfrac{2^{c_2 - 2 c_1}}{
            1 + \sum_{k = 3}^{n} (-1)^{k} \cdot 2^{-(c_k - 2 c_1)} 
        }
    }
}
\\&=& \cfrac{1}{
    2^{c_1} + \cfrac{1}{
        -2^{-c_1} + 2^{c_2 - 2 c_1} + \cfrac{1}{
            -2^{-(c_2 - 2 c_1)} + \cfrac{1}{
                -2^{c_2 - 2 c_1}\sum_{k = 3}^{n} (-1)^{k} \cdot 2^{-(c_k - 2 c_1)} 
            }
        }
    }
}
\\&=& \cfrac{1}{
    2^{c_1} + \cfrac{1}{
        2^{-c_1}(2^{c_2 - c_1} - 1) + \cfrac{1}{
            -2^{-(c_2 - 2 c_1)} + \cfrac{1}{
                -2^{c_2 - 2 c_1}\sum_{k = 3}^{n} (-1)^{k} \cdot 2^{-(c_k - 2 c_1)} 
            }
        }
    }
}
\end{matrix}
$$
