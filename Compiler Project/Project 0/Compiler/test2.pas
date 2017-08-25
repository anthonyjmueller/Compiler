(*
 * Project: TestProg
 * User: Anthony
 * Date: 8/24/2016
 *)
program test2;
var x: Integer = 0;
var y: Integer = 0;

function doublenum(a : Integer): Integer;
begin
    a := a * 2;
doublenum := a;
end;

function halfnum(a : Integer): Integer;
var b: Double;
begin
    b := a / 2;
    a := Round(b);
    halfnum := a;
end;

function divByFive( a : Integer): Integer;
begin
    if a mod 5 = 0 then divByFive:= a
    else divByFive := divByFive( a + 3)
end;

function divBySeventeen( a : Integer): Integer;
begin
    if a mod 17 = 0 then divBySeventeen:= a
    else divBySeventeen := divBySeventeen( a + 3)
end;

begin
writeln('test');
    x := 136;
    y := 7389;
    writeln(x);
    writeln(y);
    x := doublenum(x);
    writeLn(x);
    x := halfnum(x);
    writeln(x);
    x := divByFive(x);
    writeln(x);
    x:= divBySeventeen(x);
    writeln(x);
    ReadLn();
end.