function [fitresult, gof] = createFit(x, y2)
%CREATEFIT(X,Y2)
%  Create a fit.
%
%  Data for 'untitled fit 2' fit:
%      X Input : x
%      Y Output: y2
%  Output:
%      fitresult : a fit object representing the fit.
%      gof : structure with goodness-of fit info.
%
%  另请参阅 FIT, CFIT, SFIT.

%  由 MATLAB 于 25-Oct-2023 00:52:24 自动生成


%% Fit: 'untitled fit 2'.
[xData, yData] = prepareCurveData( x, y2 );

% Set up fittype and options.
ft = fittype( 'angle(1/(a*x*1i+1))*180/pi', 'independent', 'x', 'dependent', 'y' );
opts = fitoptions( 'Method', 'NonlinearLeastSquares' );
opts.DiffMaxChange = 2;
opts.DiffMinChange = 0.1;
opts.Display = 'Off';
opts.Lower = 0.1;
opts.StartPoint = 0.5;
opts.Upper = 1;

% Fit model to data.
[fitresult, gof] = fit( xData, yData, ft, opts );

% Plot fit with data.
figure( 'Name', 'untitled fit 2' );
h = plot( fitresult, xData, yData );
% hold on
% line([0.1,1/0.47],[0,0],'linestyle','--','linewidth',2);
% hold on
% line([x(4),1/0.47],[y1(4), 0], 'linestyle','--','linewidth',2);
hold on
scatter(x,y2,100)
legend( h, 'data point', 'fitted curve', 'Location', 'NorthEast', 'Interpreter', 'none' );
% Label axes
set(gca,'XScale','log') 
set(gcf,'unit','normalized','position',[0.2,0.2,0.4,0.32]);
xlabel( 'Frequency(rad/s)', 'Interpreter', 'none' );
ylabel( 'Phase(deg)', 'Interpreter', 'none' );
grid on
saveas(gcf,'p1.jpg')


