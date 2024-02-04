function [fitresult, gof] = createFit(x, y1)
%CREATEFIT(X,Y)
%  Create a fit.
%
%  Data for 'untitled fit 1' fit:
%      X Input : x
%      Y Output: y
%  Output:
%      fitresult : a fit object representing the fit.
%      gof : structure with goodness-of fit info.
%
%  另请参阅 FIT, CFIT, SFIT.

%  由 MATLAB 于 25-Oct-2023 00:01:16 自动生成


%% Fit: 'untitled fit 1'.
[xData, yData] = prepareCurveData( x, y1 );

% Set up fittype and options.
ft = fittype( '20*log10(abs(1/(a*x*1i+1)))', 'independent', 'x', 'dependent', 'y' );
opts = fitoptions( 'Method', 'NonlinearLeastSquares' );
opts.Display = 'Off';
opts.StartPoint = 0.274082371474053;

% Fit model to data.
[fitresult, gof] = fit( xData, yData, ft, opts );

% Plot fit with data.
figure( 'Name', 'untitled fit 1' );
h = plot( fitresult, xData, yData );
% hold on
% line([0.1,1/0.47],[0,0],'linestyle','--','linewidth',2);
% hold on
% line([x(4),1/0.47],[y1(4), 0], 'linestyle','--','linewidth',2);
hold on
scatter(x,y1,100)
legend( h, 'data point', 'fitted curve', 'Location', 'NorthEast', 'Interpreter', 'none' );
% Label axes
set(gca,'XScale','log') 
set(gcf,'unit','normalized','position',[0.2,0.2,0.4,0.32]);
xlabel( 'Frequency(rad/s)', 'Interpreter', 'none' );
ylabel( 'Magnitude(dB)', 'Interpreter', 'none' );
grid on
saveas(gcf,'m10.jpg')


