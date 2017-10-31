package in.ac.iitk.cse.cs252.transactions;

import org.bitcoinj.core.ECKey;
import org.bitcoinj.core.NetworkParameters;
import org.bitcoinj.core.Transaction;
import org.bitcoinj.core.Utils;
import org.bitcoinj.crypto.TransactionSignature;
import org.bitcoinj.script.Script;
import org.bitcoinj.script.ScriptBuilder;

import java.io.File;
import java.math.BigInteger;

import static org.bitcoinj.script.ScriptOpCodes.*;

/**
 * Created by bbuenz on 24.09.15.
 */
public class MultiSigTransaction extends ScriptTransaction {
    // TODO: Problem 3
    ECKey bankKey = randKey();
    ECKey cust1Key = randKey();
    ECKey cust2Key = randKey();
    ECKey cust3Key = randKey();

    public MultiSigTransaction(NetworkParameters parameters, File file, String password) {
        super(parameters, file, password);
    }

    @Override
    public Script createInputScript() {
        ScriptBuilder builder = new ScriptBuilder();
            builder.op(OP_DUP).op(OP_HASH160).data(bankKey.getPubKeyHash()).op(OP_EQUALVERIFY).op(OP_CHECKSIGVERIFY).op(OP_1).data(cust1Key.getPubKey).data(cust2Key.getPubKey).data(cust3Key.getPubKey).op(OP_3).op(OP_CHECKMULTISIG);
            return builder.build();
    }

    @Override
    public Script createRedemptionScript(Transaction unsignedTransaction) {
            TransactionSignature txSig = sign(unsignedTransaction, cust1Key);
            TransactionSignature txSigBank = sign(unsignedTransaction, bankKey);
            ScriptBuilder builder = new ScriptBuilder();
            builder.op(OP_0).data(txSig.encodeToBitcoin()).data(txSigBank.encodeToBitcoin()).data(bankKey.getPubKey);
            return builder.build();
    }
}
