:git remote add origin https://github.com/LukeMS/dnf-c.git
:@git config --global user.email "lucas.morais.siqueira@gmail.com"
:@git config --global user.name "Lucas de Morais Siqueira"

@git add --all

:@set /p msg="Describe the commit: "
:@git commit -m "%msg%"

@git commit -m "travis"
@git push origin master

@pause
