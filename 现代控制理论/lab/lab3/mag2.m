function [fitresult, gof] = createFit(x, y3)
%CREATEFIT(X,Y3)
%  Create a fit.
%
%  Data for 'untitled fit 2' fit:
%      X Input : x
%      Y Output: y3
%  Output:
%      fitresult : a fit object representing the fit.
%      gof : structure with goodness-of fit info.
%
%  另请参阅 FIT, CFIT, SFIT.

%  由 MATLAB 于 25-Oct-2023 01:04:14 自动生成


%% Fit: 'untitled fit 2'.
[xData, yData] = prepareCurveData( x, y3 );

% Set up fittype and options.
ft = fittype( '20*log10(abs(-10/((a*x*1i+1)*(b*x*1i+1))))', 'independent', 'x', 'dependent', 'y' );
opts = fitoptions( 'Method', 'NonlinearLeastSquares' );
opts.DiffMaxChange = 2;
opts.DiffMinChange = 0.1;
opts.Display = 'Off';
opts.Lower = [-Inf 0];
opts.StartPoint = [0.970592781760616 0.957166948242946];
opts.Upper = [Inf 2];

% Fit model to data.
[fitresult, gof] = fit( xData, yData, ft, opts );

% Plot fit with data.
figure( 'Name', 'untitled fit 2' );
h = plot( fitresult, xData, yData );
hold on
line([x(1),1],[20,20],'linestyle','--','linewidth',2);
hold on
line([1,10],[20, 0], 'linestyle','--','linewidth',2);
hold on
line([x(4),10],[y3(4), 0], 'linestyle','--','linewidth',2);
hold on
scatter(x,y3,100)
legend( h, 'data point', 'fitted curve', 'Location', 'NorthEast', 'Interpreter', 'none' );
% Label axes
set(gca,'XScale','log') 
set(gcf,'unit','normalized','position',[0.2,0.2,0.4,0.32]);
xlabel( 'Frequency(rad/s)', 'Interpreter', 'none' );
ylabel( 'Magnitude(dB)', 'Interpreter', 'none' );
grid on
saveas(gcf,'m21.jpg')


