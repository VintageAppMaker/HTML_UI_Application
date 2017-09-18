program DelBrowser;



uses
  Forms,
  frmMain in 'frmMain.pas' {frmMainView},
  IEBrowser in 'IEBrowser.pas',
  iAppBrowser in 'iAppBrowser.pas',
  PageSelector in 'PageSelector.pas',
  iDBEng in 'iDBEng.pas',
  TDBEng in 'TDBEng.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.MainFormOnTaskbar := True;
  Application.CreateForm(TfrmMainView, frmMainView);
  Application.Run;
end.
