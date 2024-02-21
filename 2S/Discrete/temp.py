import pandas as pd
import io
from sympy import *


variables=['p', 'q', 'r', 's', 't']
expression1=lambda q,r: q or r
expression2=lambda p,r: p or r
claim_expression=lambda q,r,p: Implies(q or r, p or r)

data=[]

for p in (True, False):
    for q in (True, False):
        for r in (True, False):
            for t in (True, False):
                for s in (True, False):
                    result1=expression1(q,r)
                    result2=expression2(p,r)
                    claim_result=claim_expression(q,r,p)
                    data.append([p,q,r,t,s,result1,result2,claim_result])
                      
df=pd.DataFrame(data, columns=['p','q','r','t','s','q|r','p|r','(q|r)->(p|r)'])
print(df)          


