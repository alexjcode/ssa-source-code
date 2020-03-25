# AnyPIA Source Code
https://docs.google.com/document/d/13cmLTbSPMelH3Trwn97XvbacHwunfRQp0ScHgDng_-c/edit#

Screenshots from our tour of the policy code: https://drive.google.com/drive/folders/1Y-3GPoxF3Z_QLYFraHPr9wjUfo2rVczS


### Idea: Enscripten this sourcecode to use it from JS
- `oactobjs32/` might be enough. `Module.ccall()` as the connection btwn JS<>

## Files that may contain portions of the SSA calculation formula / data:
- https://github.com/alexjcode/ssa-source-code/blob/master/oactobjs32/piadata/awbidtnf.cpp (Max Earnings creditable)
- https://github.com/alexjcode/ssa-source-code/blob/master/oactobjs32/include/SgaGeneral.h
- https://github.com/alexjcode/ssa-source-code/blob/master/oactobjs32/piadata/SgaGeneral.cpp
- https://github.com/alexjcode/ssa-source-code/blob/master/oactobjs32/include/avgwg.h
- https://github.com/alexjcode/ssa-source-code/blob/master/oactobjs32/piadata/avgwg.cpp
- https://github.com/alexjcode/ssa-source-code/blob/master/oactobjs32/include/EarnProject.h
- https://github.com/alexjcode/ssa-source-code/blob/master/oactobjs32/piadata/EarnProject.cpp

## Predicting SSA variables for future years

#### ✅ Bendpoints
- (Unknown formula, but has detailed predictions in the Trustees report)
- https://www.ssa.gov/OACT/TR/2019/tr2019.pdf#page=127
- https://www.ssa.gov/OACT/TR/2019/tr2019.pdf#page=128

#### ✅ Benefit Reduction
- (Stays the same for the foreseeable future)

#### *️⃣ ??? => Substantial Earnings (WEP)
- (Unknown prediction formula) 
- https://www.ssa.gov/pubs/EN-05-10045.pdf
- "Substantial Earnings" is a yearly earnings threshold which determines how much pension a worker will receive based on how "substantial" their salary was across various years

- Here is where the YOC aka Substantial Earnings table gets updated: https://github.com/alexjcode/ssa-source-code/blob/a179e28d63cb2966fae53e76e4aab73dea7a90cf/oactobjs32/piadata/piaparms.cpp#L616 Code is very complex. Also need to understand the other piaparms* files: several use Assumptions.
- Assumptions: The Assumptions class and tab visible in AnyPIA is relevant only when the person has not yet (either: retired OR reached retirement age, not sure which??). It takes as parameters the current calendar year and the max projected year (is this 2100 or retirement age?)  We could use it to Could track average earnings, but not relevant to substantial earnings in an obvious way.
- PiaMethod seems to implement WEP category of the person's situation here, counting years based on Substantial Earnings: https://github.com/alexjcode/ssa-source-code/blob/master/oactobjs32/piadata/PiaMethod.cpp#L91

#### ✅ COLA
- (Formula is publicly available, uses 3rd quarter CPI-W of current and past year)
- https://www.ssa.gov/OACT/TR/2019/tr2019.pdf#page=112
- https://www.ssa.gov/OACT/COLA/latestCOLA.html

#### ✅  Max Wages Taxable / Max Wages Creditable
In the official calculator we can see from the "Maximum" shown in the wage entry dialog in future years that they just use the current year's maximum. Our app should do the same.

- https://github.com/alexjcode/ssa-source-code/blob/master/oactobjs32/piadata/awbidtnf.cpp
- (Unknown prediction formula)
- Not necessarily correlated with Average Wages taxable
- https://www.ssa.gov/OACT/TR/2019/tr2019.pdf#page=112
- https://secure.ssa.gov/POMS.NSF/lnx/0301404300
- https://www.ssa.gov/policy/docs/statcomps/supplement/2017/2a1-2a7.html#table2.a3
- https://www.ssa.gov/policy/docs/statcomps/supplement/2017/glossary.html#maxtax
- https://secure.ssa.gov/apps10/poms/images/poms19/19700/G-SL_70001.001.pdf
- https://secure.ssa.gov/poms.nsf/lnx/0301401015
- https://www.ssa.gov/OP_Home/ssact/title02/0230.htm
- https://www.ssa.gov/regulations/

#### ✅ Average Wage Index
- (Has detailed predictions in the Trustees report)
- https://www.ssa.gov/OACT/TR/2019/tr2019.pdf#page=123
- https://www.ssa.gov/OACT/TR/2019/tr2019.pdf#page=224

## Tables
- https://docs.google.com/spreadsheets/d/1EXfjoFpx6e5ypw5te45fDWkBXwFolDSbgHJv9rpdMB0/edit#gid=1069245443
- https://docs.google.com/spreadsheets/d/1rDQXvMoV4d5uQBtvoCIEthqsA0E1TpZS17enqitNiSw/edit#gid=442134127

#### Real wage differential
- Real wage differential = Δ Average Annual Wage in Covered Employment - Δ CPI-W
- (Might be used in a formula somewhere)
https://www.ssa.gov/OACT/TR/2019/tr2019.pdf#page=111
