# Results

**Basic EICAR test (control experiment)**

Detection ratio: 50 / 57 

https://www.virustotal.com/en/file/131f95c51cc819465fa1797f6ccacf9d494aaaff46fa3eac73ae63ffbdfd8267/analysis/1425476118/

**Basic EICAR with padding (control experiment)**
Added padding to test for REGEX.

Detection ratio: 5/57 

https://www.virustotal.com/en/file/476a1a56169877953e0d23998cca20b2b2514730133ecda3726b79caca0ee424/analysis/1425476045/

**Is registry scanned - Create registry key**
This adds the EICAR string to a registry key

Detection ratio: 0 / 57 

https://www.virustotal.com/en/file/324c9e86303103d5c73c19d3a4f43b1cd75ec057a652cbd5934718d0176debce/analysis/1425400442/

**Is filesystem emulated**
This writes the EICAR string to a file on the virtual file system.

Detection ratio: 3 / 57 

https://www.virustotal.com/en/file/fe5d169ad6cb395b7f0ce42a1a4e46c03f2f6198aba9aac190185d9c828c3cee/analysis/1425387916/

**Is HTTP traffic scanned**
This writes the EICAR string to the useragent in the header of a http request.

Detection ratio: 1 / 57

https://www.virustotal.com/en/file/28e1048bba9ff811961308a1bcf8182c330bccd94e576a06e6033b07f2e14f5b/analysis/1425383006/

**Are known suspicious domains flagged**
This creates a http request to a known suspicious domain from a bad-list.

Detection ratio: 1 / 57

https://www.virustotal.com/en/file/06f4804b79237c81b4686ced155fd843123b6397f506c1c10c7dbd2e54e21efc/analysis/1425385102/

**Is screen emulated**
Take a screenshot and determine is surface area is greater than 500px. Otherwise EICAR is written to file on VFS.

Detection ratio: 0 / 57

https://www.virustotal.com/en/file/cb41378405915f3d58b2cf36a585f03a2c861664384fbce47f72543570c8bdaf/analysis/1425470236/

**Is RAM emulated**
Allocate memory, fill with 'A' character, calculate crc32 checksum, compare to pre-defined value, then if value is correct write EICAR file to VFS.

Detection ratio: 3 / 57

https://www.virustotal.com/en/file/886044135f6c5e15735d80ca3bf2ad2a15f0290af87de0cf573d9c075183639a/analysis/1425479793/

**Is memory scanned**
Portable executable .text and .data sections appear in memory in the same structure as they do on disk, however character arrays are not contigious, this test allocates memory and creates a contigious block in which the EICAR string is placed.

Detection ratio: 0 / 57

https://www.virustotal.com/en/file/ba23ce469d9ceeda86d8ff5f61cf197f60f0905a41c2dcd80433e7e1f7452782/analysis/1426337514/

**Are contigious strings scanned**
Character arrays declared compiled with "static const char" will appear as a contigious block of memory in strings.

Detection ratio: 1 / 57

https://www.virustotal.com/en/file/c2c1ebc50122d816281ede9b87066b0dfc14e74846099e7671934d2a00e52efe/analysis/1426338254/

**PE Inject explorer.exe**
Inject a complete exeutable file image into explorer.exe and execute it.

Detection ratio: 0 / 57

https://www.virustotal.com/en/file/aaa27d270e30c4bed65aa29b234f6da289d3f46b6e68d74589ec0776a7410495/analysis/1425911509/
