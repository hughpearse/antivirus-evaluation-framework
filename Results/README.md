# Results

**Create Registry key**
This adds the EICAR string to a registry key

Detection ratio: 0 / 57 

https://www.virustotal.com/en/file/324c9e86303103d5c73c19d3a4f43b1cd75ec057a652cbd5934718d0176debce/analysis/1425400442/

**Filesystem test dropper**
This writes the EICAR string to a file on the virtual file system.

Detection ratio: 3 / 57 

https://www.virustotal.com/en/file/fe5d169ad6cb395b7f0ce42a1a4e46c03f2f6198aba9aac190185d9c828c3cee/analysis/1425387916/

**EICAR in HTTP header**
This writes the EICAR string to the useragent of a http request.

Detection ratio: 1 / 57

https://www.virustotal.com/en/file/28e1048bba9ff811961308a1bcf8182c330bccd94e576a06e6033b07f2e14f5b/analysis/1425383006/

**Are known suspicious domains flagged**
This creates a http request to a known suspicious domain from a bad-list.

Detection ratio: 1 / 57

https://www.virustotal.com/en/file/06f4804b79237c81b4686ced155fd843123b6397f506c1c10c7dbd2e54e21efc/analysis/1425385102/

**Screenshot size check**
Take a screenshot and determine is surface area is greater than 500px.

Detection ratio: 0 / 57

https://www.virustotal.com/en/file/cb41378405915f3d58b2cf36a585f03a2c861664384fbce47f72543570c8bdaf/analysis/1425470236/

**EICAR with padding**
Added padding to test for REGEX.

https://www.virustotal.com/en/file/476a1a56169877953e0d23998cca20b2b2514730133ecda3726b79caca0ee424/analysis/1425472822/
