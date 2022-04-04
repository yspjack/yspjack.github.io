---
title: MS Office File to PDF
date: 2022-04-01 00:53:53
tags:
---
## doc to pdf

https://stackoverflow.com/a/6018039

```python
import sys
import os
import comtypes.client

wdFormatPDF = 17

in_file = os.path.abspath(sys.argv[1])
out_file = os.path.abspath(sys.argv[2])

word = comtypes.client.CreateObject('Word.Application')
doc = word.Documents.Open(in_file)
doc.SaveAs(out_file, FileFormat=wdFormatPDF)
doc.Close()
word.Quit()
```

<!--more-->

using `pywin32`:

```python
import win32com.client
# ...
word = win32com.client.Dispatch('Word.Application')
# ...
```


## ppt to pdf

```js
var source=WScript.Arguments.Item(0);
//var target=WScript.Arguments.Item(1);
var target=source.substr(0, source.lastIndexOf('.'))+".pdf";
PP = new ActiveXObject("PowerPoint.Application");
PRSNT = PP.presentations.Open(source,0,0,0)
//PRSNT.SaveCopyAs(target,32);
//https://msdn.microsoft.com/en-us/vba/powerpoint-vba/articles/ppsaveasfiletype-enumeration-powerpoint
PRSNT.SaveAs(target,32);
PRSNT.Close();
PP.Quit();

```

## Reference

https://docs.microsoft.com/en-us/office/vba/api/word.wdsaveformat

https://docs.microsoft.com/en-us/office/vba/api/powerpoint.ppsaveasfiletype

