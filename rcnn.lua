require 'dp'
require 'rnn'
require 'optim'

ds = dp.NotMnist()

model = nn.Sequential()

channels = ds:imageSize('c')

maps = 20

cnn = nn.Sequential()
-- cnn:add(nn.TemporalConvolution(channels, maps, 7))
-- cnn:add(nn.TemporalMaxPooling(3))
cnn:add(nn.Collapse(2))
outsize = cnn:outside{1, ds:imageSize('w'), ds:imageSize('c')}
outsize = outsize[2]

print("OUTSIZE")
print(outsize)

nn.FastLSTM.usenngraph = true

hiddenSize = 256
classes = #(ds:classes())


model:add(nn.View(ds:imageSize('h'), ds:imageSize('w'), ds:imageSize('c')):setNumInputDims(3))
model:add(nn.SplitTable(1, 3))
model:add(nn.Sequencer(cnn))
model:add(nn.Sequencer(nn.FastLSTM(outsize, hiddenSize)))
model:add(nn.SelectTable(-1))
model:add(nn.Linear(hiddenSize, classes))
model:add(nn.LogSoftMax())

model:float()

criterion = nn.ClassNLLCriterion()

criterion = criterion:float()

print(model)

-- tst = torch.randn(2, ds:imageSize('c'), ds:imageSize('h'), ds:imageSize('w')):float()
-- print(tst)
-- tst = nn.View(ds:imageSize('h'), ds:imageSize('w'), ds:imageSize('c')):setNumInputDims(3):forward(tst)
-- print(tst)
-- tst = nn.SplitTable(1, 3):forward(tst)
-- print(tst)
-- tst = nn.Sequencer(cnn):forward(tst)
-- print(tst)
-- tst = nn.Sequencer(nn.FastLSTM(outsize, hiddenSize)):float():forward(tst)
-- print(tst)

opt = {}
opt.momentum = 0.9
opt.learningRate = 0.1
opt.maxOutNorm = 1.0
opt.progress = true
opt.batchSize = 32

print(classes)

x, dx = model:getParameters()

function feval(x)
	return 0, dx
end

sgd_params = {
	learningRate = 0.1
}

train = dp.Optimizer{
   acc_update = opt.accUpdate,
   loss = criterion,
   epoch_callback = function(model, report) -- called every epoch
      --do nothing
   end,
   callback = function(model, report) -- called every batch
      optim.adagrad(feval, x, sgd_params)
      model:zeroGradParameters()
   end,
   feedback = dp.Confusion(),
   sampler = dp.ShuffleSampler{batch_size = opt.batchSize},
   progress = opt.progress
}
valid = ds:validSet() and dp.Evaluator{
   feedback = dp.Confusion(),  
   sampler = dp.Sampler{batch_size = opt.batchSize},
   progress = opt.progress
}
test = ds:testSet() and dp.Evaluator{
   feedback = dp.Confusion(),
   sampler = dp.Sampler{batch_size = opt.batchSize},
   progress = opt.progress
}

--[[Experiment]]--
xp = dp.Experiment{
   model = model,
   optimizer = train,
   validator = ds:validSet() and valid,
   tester = ds:testSet() and test,
   observer = {
      dp.FileLogger(),
      dp.EarlyStopper{
         error_report = {'validator','feedback','confusion','accuracy'},
         maximize = true,
         max_epochs = opt.maxTries
      }
   },
   random_seed = os.time(),
   max_epoch = opt.maxEpoch
}

xp:run(ds)
