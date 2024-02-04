function [fitresult, gof] = createFit(x, y4)
%CREATEFIT(X,Y4)
%  Create a fit.
%
%  Data for 'untitled fit 1' fit:
%      X Input : x
%      Y Output: y4
%  Output:
%      fitresult : a fit object representing the fit.
%      gof : structure with goodness-of fit info.
%
%  另请参阅 FIT, CFIT, SFIT.

%  由 MATLAB 于 25-Oct-2023 01:14:30 自动生成


%% Fit: 'untitled fit 1'.
[xData, yData] = prepareCurveData( x, y4 );

% Set up fittype and options.
ft = fittype( '180*angle(-10/((a*x*1i+1)*(b*x*1i+1)))/pi', 'independent', 'x', 'dependent', 'y' );
opts = fitoptions( 'Method', 'NonlinearLeastSquares' );
opts.Display = 'Off';
opts.StartPoint = [0.0357116785741896 0.849129305868777];

% Fit model to data.
[fitresult, gof] = fit( xData, yData, ft, opts );

% Plot fit with data.
figure( 'Name', 'untitled fit 1' );
h = plot( fitresult, xData, yData );
hold on
scatter(x,y4,100)
legend( h, 'y4 vs. x', 'untitled fit 1', 'Location', 'NorthEast', 'Interpreter', 'none' );
% Label axes
set(gca,'XScale','log') 
set(gcf,'unit','normalized','position',[0.2,0.2,0.4,0.32]);
xlabel( 'Frequency(rad/s)', 'Interpreter', 'none' );
ylabel( 'Phase(deg)', 'Interpreter', 'none' );
grid on
saveas(gcf,'p2.jpg')


