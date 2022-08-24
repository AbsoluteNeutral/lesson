0. go to your working directonary

1. install pkg locally
npm install -D pkg

2. in package.json, add the corresponding line:
note:
this build is for node version 14, windows, x64 
"scripts": {
    "build": "pkg -t node14-win-x64 --output ./my_exe_name.exe my_app_file.js"
  },
  
3. npm run-script build
